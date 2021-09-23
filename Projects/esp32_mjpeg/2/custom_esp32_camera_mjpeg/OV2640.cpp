#include "OV2640.h"

#include "img_converters.h"

#include "fb_gfx.h"

#define TAG "OV2640"

#define FACE_COLOR_WHITE  0x00FFFFFF
#define FACE_COLOR_BLACK  0x00000000
#define FACE_COLOR_RED    0x000000FF
#define FACE_COLOR_GREEN  0x0000FF00
#define FACE_COLOR_BLUE   0x00FF0000
#define FACE_COLOR_YELLOW (FACE_COLOR_RED | FACE_COLOR_GREEN)
#define FACE_COLOR_CYAN   (FACE_COLOR_BLUE | FACE_COLOR_GREEN)
#define FACE_COLOR_PURPLE (FACE_COLOR_BLUE | FACE_COLOR_RED)

static void draw_face_boxes(dl_matrix3du_t *image_matrix, box_array_t *boxes){
    int x, y, w, h, i;
    uint32_t color = FACE_COLOR_YELLOW;
    
    fb_data_t fb;
    fb.width = image_matrix->w;
    fb.height = image_matrix->h;
    fb.data = image_matrix->item;
    fb.bytes_per_pixel = 3;
    fb.format = FB_BGR888;
    
    for (i = 0; i < boxes->len; i++){
      // rectangle box
      x = (int)boxes->box[i].box_p[0];
      y = (int)boxes->box[i].box_p[1];
      w = (int)boxes->box[i].box_p[2] - x + 1;
      h = (int)boxes->box[i].box_p[3] - y + 1;
      fb_gfx_drawFastHLine(&fb, x, y, w, color);
      fb_gfx_drawFastHLine(&fb, x, y+h-1, w, color);
      fb_gfx_drawFastVLine(&fb, x, y, h, color);
      fb_gfx_drawFastVLine(&fb, x+w-1, y, h, color);
        
      #if 0
      // landmark
      int x0, y0, j;
      for (j = 0; j < 10; j+=2) {
        x0 = (int)boxes->landmark[i].landmark_p[j];
        y0 = (int)boxes->landmark[i].landmark_p[j+1];
        fb_gfx_fillRect(&fb, x0, y0, 3, 3, color);
      }
      #endif
   }
}

void OV2640::run(void)
{
//  int face_id = 0;
//
//  uint8_t _jpg_buf = NULL;
//  
//  size_t _jpg_buf_len = 0;
//
//  dl_matrix3du_t *image_matrix = NULL;
//  
//  if (fb) {
//    image_matrix = dl_matrix3du_alloc(1, fb->width, fb->height, 3);
//
//    if (image_matrix) {
//      if (fmt2rgb888(fb->buf, fb->len, fb->format, image_matrix->item)) {
//        box_array_t *net_boxes = face_detect(image_matrix, &_mtmn_config);
//
//        if (net_boxes || fb->format != PIXFORMAT_JPEG) {
//
//          draw_face_boxes(image_matrix, net_boxes);
//          free(net_boxes->score);
//          free(net_boxes->box);
//          free(net_boxes->landmark);
//          free(net_boxes);
//        } 
//        else {
//          Serial.println("net_boxes error");
//        }
//
//        esp_camera_fb_return(fb);
//      }
//      else {
//        Serial.println("fmt error");
//      }
//    }
//    else {
//      Serial.println("image_matrix error");
//    }
//    dl_matrix3du_free(image_matrix);
//  } else {
//    Serial.println("fb error");
//  }

  if (fb)
    esp_camera_fb_return(fb);
        
  fb = esp_camera_fb_get();
}

void OV2640::runIfNeeded(void)
{
  Serial.println("running...");
    if (!fb)
        run();
}

int OV2640::getWidth(void)
{
    runIfNeeded();
    return fb->width;
}

int OV2640::getHeight(void)
{
    runIfNeeded();
    return fb->height;
}

size_t OV2640::getSize(void)
{
    runIfNeeded();
    if (!fb)
        return 0; // FIXME - this shouldn't be possible but apparently the new cam board returns null sometimes?
    return fb->len;
}

uint8_t *OV2640::getfb(void)
{
    runIfNeeded();
    if (!fb)
        return NULL; // FIXME - this shouldn't be possible but apparently the new cam board returns null sometimes?

    return fb->buf;
}

framesize_t OV2640::getFrameSize(void)
{
    return _cam_config.frame_size;
}

void OV2640::setFrameSize(framesize_t size)
{
    _cam_config.frame_size = size;
}

pixformat_t OV2640::getPixelFormat(void)
{
    return _cam_config.pixel_format;
}

void OV2640::setPixelFormat(pixformat_t format)
{
    switch (format)
    {
    case PIXFORMAT_RGB565:
    case PIXFORMAT_YUV422:
    case PIXFORMAT_GRAYSCALE:
    case PIXFORMAT_JPEG:
        _cam_config.pixel_format = format;
        break;
    default:
        _cam_config.pixel_format = PIXFORMAT_GRAYSCALE;
        break;
    }
}

esp_err_t OV2640::init(camera_config_t config, mtmn_config_t mtmn_config)
{
    memset(&_cam_config, 0, sizeof(_cam_config));
    memcpy(&_cam_config, &config, sizeof(config));

    esp_err_t err = esp_camera_init(&_cam_config);
    if (err != ESP_OK)
    {
        printf("Camera probe failed with error 0x%x", err);
        return err;
    }
    // ESP_ERROR_CHECK(gpio_install_isr_service(0));

    memset(&_mtmn_config, 0, sizeof(_mtmn_config));
    memcpy(&_mtmn_config, &mtmn_config, sizeof(mtmn_config));
    
    return ESP_OK;
}
