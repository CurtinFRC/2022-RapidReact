#include "Vision.h" // required before other #includes
#include "UDP_TransferNT.h"
//#include "ImageProcessing/Contours.h"

using namespace UDP_TransferNT;

struct Images {
  CJ::Image originImage;
  CJ::Image filteredImage;
  CJ::Image contouredImage;
  CJ::Image boundImage;
  CJ::Image filtered_contours;
};
/**
 * Example Layer for Vision App
 * (All in one layer. Webcam, networking and display. Should be split up into multiple layers.)
 */
class CaptureLayer : public CJ::Layer {
public:
  CaptureLayer(CJ::Application &app, Images &images) : Layer("Capture Layer"), _app(app), _images(images) {
    CJ_PRINT_INFO("Capture Layer Created");
  }

  void onAttach() override {
    CJ_PRINT_INFO("Capture Layer Attached");
    #ifdef COPROC
    _camera.config.port = 0;
    #else
    _camera.config.port = 1;
    #endif
    _camera.config.fps = 30;
    _camera.config.autoExposure = false;
    _camera.config.exposure = -11;

    _camera.config.name = "Example Camera";

    _images.originImage.name = "Origin Image";
    _images.filteredImage.name = "Filtered Image";
    _images.contouredImage.name = "Contoured Image";
    _images.boundImage.name = "Bound Image";



    if (_camera.init() != 0) {
      CJ_PRINT_ERROR("Could not init camera");
      _app.setRunning(false);
    }
  }

  void onDetach() override {
    CJ_PRINT_WARN("Capture Layer Detached");
  }

  void onUpdate() override {
    _camera.capture(_images.originImage);
  }

private:
  CJ::Application &_app;
  Images &_images;
  CJ::Camera _camera;
};

class FilterLayer : public CJ::Layer {
public:
  FilterLayer(CJ::Application &app, Images &images) : Layer("Filter Layer"), _app(app), _images(images) {
    CJ_PRINT_INFO("Filtered Layer created");
  }

  void onAttach() override {
    //CJ::ColourFilter::createFilterTrackbar(_options);
  }

  void onUpdate() override {
    CJ::ColourFilter::filter(_images.originImage, _images.filteredImage, _options);
  }

private:
  CJ::ColourFilter::GrayScale_Options _options {8, 0, 0, 19, 255};
  CJ::Application &_app;
  Images &_images;
};
//void createContoursTrackbar(int &threshold);

class ContoursLayer : public CJ::Layer {
public:
  ContoursLayer(CJ::Application &app, Images &images) : Layer("Contours Layer"), _app(app), _images(images) {
    CJ_PRINT_INFO("Contours Layer Created");
  }

  void onAttach() override {
    //CJ::Contours::createContoursTrackbar(_threshold);
    
  }

  void onDetach() override {
    CJ_PRINT_WARN("Contours Layer Detached");
  }

  void onUpdate() override {
    CJ::Contours::detectContours(_images.filteredImage, _images.contouredImage);
    //CJ::ColourFilter::filter(_images.filteredImage, _images.contouredImage, _options); // disable draw is false. (it will draw the contours onto the output image and we can display it later)

  }

private:
  //CJ::Contours::GrayScale_Options _options;
  //int _threshold;
  CJ::Application &_app;
  Images &_images;
};

class BoundingLayer : public CJ::Layer {
public:
  BoundingLayer(CJ::Application &app, Images &images) : Layer("Bounding Layer"), _app(app), _images(images) {
    CJ_PRINT_INFO("Bounding Layer Created");
    _network = new Network(Network::Type::CLIENT, Network::ConnectionType::IP_SPECIFIC);
  }

  void onAttach() override {
    CJ_PRINT_INFO("Bounding Layer Attached");
    
    _network->getSocket().setIP("10.47.88.150"); // 10.47.88.2
    _network->getSocket().setPort(5801);
    _network->init();

  //	_outputImg.name = "Bounding Image";
  }

  void onDetach() override {
    CJ_PRINT_WARN("Bounding Layer Detached");
  }

  void onUpdate() override {
    CJ::Bound::drawConvexHull(_images.contouredImage, _images.contouredImage); // draw hull onto _contourImg

    if (_images.contouredImage.data.empty()) {
      return;
    }
    // Setup poly/Bounding rect
    std::vector<std::vector<cv::Point>> contours_poly(_images.contouredImage.hull.size());
    std::vector<cv::Rect> boundRect(_images.contouredImage.hull.size());
    cv::Rect biggestRect;
    // object_xy = CJ::Bound::drawBoundingBox(_images.contouredImage, _images.boundImage); // draw bounding box and get center points

    CJ::BoundingPoints center;
    double biggestArea = 0;
    int biggestIndex = 0;
    
    _images.boundImage.data = cv::Mat::zeros(_images.contouredImage.data.size(), CV_8UC3);
    for (size_t i = 0; i < _images.contouredImage.hull.size(); i++) {
      cv::approxPolyDP(_images.contouredImage.hull[i], contours_poly[i], 3, true);
      boundRect[i] = cv::boundingRect(contours_poly[i]);
     
      double bufferArea = (boundRect[i].width * boundRect[i].height);
      double bufferWidth = (boundRect[i].width);
      double bufferHeight = (boundRect[i].height);

      double area = cv::contourArea(_images.contouredImage.contours[i]);
      double solidity = area / cv::contourArea(_images.contouredImage.hull[i]);

       if (bufferArea > biggestArea){ //&& area > 300 && solidity < 0.75 ){
         center.center_x = boundRect[i].x + boundRect[i].width/2;
         center.center_y = boundRect[i].y + boundRect[i].height/2;
         biggestRect = boundRect[i];
         biggestArea = bufferArea;
         biggestIndex = i;
       }

    }
    double bufferWidth = (biggestRect.width);
    double bufferHeight = (biggestRect.height);
    
    cv::Point centerRect(center.center_x, center.center_y);
    cv::Point width(biggestRect.width);
    cv::Point height(biggestRect.height);
    //std::vector<std::vector<cv::Point>> widthRect(width.width);
    cv::putText(_images.boundImage.data, "xy(" + std::to_string(center.center_x) + "," + std::to_string(center.center_y) + ")", (centerRect + cv::Point(-25,25)), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,30,255));
    cv::putText(_images.boundImage.data, "width(" + std::to_string(biggestRect.width) + ")", (centerRect + cv::Point(-50,50)), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,30,255));
    cv::putText(_images.boundImage.data, "height(" + std::to_string(biggestRect.height) + ")", (centerRect + cv::Point(25, -25)), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0, 30, 255));
    cv::circle(_images.boundImage.data, centerRect, 3, cv::Scalar(255, 0, 0));
    cv::drawContours(_images.boundImage.data, contours_poly, biggestIndex, cv::Scalar(255,0,0));
    cv::rectangle(_images.boundImage.data, biggestRect.tl(), biggestRect.br(), cv::Scalar(255, 0, 0));

    _dpSend.setDecimals(0, center.center_x);
    _dpSend.setDecimals(1, center.center_y);
    _dpSend.setDecimals(2, _app.getDt());

    _network->dpSend(_dpSend);
  }
  
private:
  CJ::Application &_app;
  Images &_images;
  CJ::BoundingPoints object_xy;
  DataPacket _dpSend;
  Network *_network;

};

class DisplayLayer : public CJ::Layer {
public:
  DisplayLayer(CJ::Application &app, Images &images) : Layer("Display Layer"), _app(app), _images(images) {}

  void onAttach() override {
    _streamServer.start();
    // _streamServerFilter.start();
  }

  void onDetach() override {
    _streamServer.stop();
    // _streamServerFilter.stop();
  }

  void onUpdate() override {
    if (CJ::Output::display(30, _images.boundImage) == 27) {
      _app.setRunning(false);
    }

    // _streamServerFilter.output(_images.filteredImage);
    _streamServer.output(_images.originImage);
  }
private:
  CJ::Output::Stream _streamServer{5802};
  // CJ::Output::Stream _streamServerFilter{5803};
  CJ::Application &_app;
  Images &_images;
};

/**
  * Example Vision application
//   */
class VisionApplication : public CJ::Application {
public:
  VisionApplication() : CJ::Application("Vision Tracking") {
  
    CJ_PRINT_INFO("Vision App created");
    pushLayer(new CaptureLayer(get(), _images));
    pushLayer(new FilterLayer(get(), _images));
    pushLayer(new ContoursLayer(get(), _images));
    pushLayer(new BoundingLayer(get(), _images));
    pushLayer(new DisplayLayer(get(), _images));
  }

  ~VisionApplication() {
    CJ_PRINT_WARN("Test App Destroyed");
  }
private: 
  Images _images;
};

CJ_CREATE_APPLICATION(VisionApplication)