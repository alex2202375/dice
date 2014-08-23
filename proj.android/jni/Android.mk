LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/2d)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp


LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
					../../Classes/CommonUtil.cpp \
					../../Classes/GameBackgroundLayer.cpp \
					../../Classes/GameLayer.cpp \
					../../Classes/GameScene.cpp \
					../../Classes/HeadLayer.cpp \
					../../Classes/HeadScene.cpp \
					../../Classes/InitBackgroundLayer.cpp \
					../../Classes/LoadingLayer.cpp \
					../../Classes/LoadingScene.cpp \
					../../Classes/LogicalEngine.cpp \
					../../Classes/LoginLayer.cpp \
					../../Classes/LoginScene.cpp \
					../../Classes/NetEngine.cpp \
					../../Classes/Player.cpp \
					../../Classes/RegisterLayer.cpp \
					../../Classes/RegisterScene.cpp \
					../../Classes/Room.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../cocos2d \
                    $(LOCAL_PATH)/../../cocos2d/cocos \
                    $(LOCAL_PATH)/../../cocos2d/cocos/2d \
                    $(LOCAL_PATH)/../../cocos2d/cocos/ui \
                    $(LOCAL_PATH)/../../cocos2d/cocos/base \
                    $(LOCAL_PATH)/../../cocos2d/cocos/math \
					$(LOCAL_PATH)/../../cocos2d/extensions \
                    $(LOCAL_PATH)/../../libpomelo/include \
                    $(LOCAL_PATH)/../../libpomelo/deps/jansson/src \
                    $(LOCAL_PATH)/../../libpomelo/deps/uv/include \
					
					
					                                                            
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

#LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
#LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
#LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
#LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
#LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += pomelo_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_ui_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

#$(call import-module,Box2D)
#$(call import-module,editor-support/cocosbuilder)
#$(call import-module,editor-support/spine)
#$(call import-module,editor-support/cocostudio)
$(call import-module,network)
$(call import-module,extensions)
$(call import-module,libpomelo)
$(call import-module,ui)
