#include "OV2640.h"

#include "img_converters.h"

#define TAG "OV2640"

void OV2640::run(void)
{
  int face_id = 0;

  uint8_t _jpg_buf = NULL;
  
  size_t _jpg_buf_len = 0;

  dl_matrix3du_t *image_matrix = NULL;
  
  if (fb) {
    image_matrix = dl_matrix3du_alloc(1, fb->width, fb->height, 3);

    if (image_matrix) {
      if (fmt2rgb888(fb->buf, fb->len, fb->format, image_matrix->item)) {
        box_array_t *net_boxes = face_detect(image_matrix, &_mtmn_config);
      }
    }
  }
        
  fb = esp_camera_fb_get();
}

void OV2640::runIfNeeded(void)
{
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
