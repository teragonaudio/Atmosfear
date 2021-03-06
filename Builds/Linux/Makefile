# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../../../sdk/vstsdk2.4 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -fPIC -O0 -std=c++11 -I../../Third-Party/TeragonGuiComponents/Components/PluginParameters/include -I../../Third-Party/TeragonGuiComponents/Components/Plugin -I../../Third-Party/TeragonGuiComponents/Components/Source
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -shared -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 

  TARGET := Atmosfear.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../../../sdk/vstsdk2.4 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -fPIC -O3 -std=c++11 -I../../Third-Party/TeragonGuiComponents/Components/PluginParameters/include -I../../Third-Party/TeragonGuiComponents/Components/Plugin -I../../Third-Party/TeragonGuiComponents/Components/Source
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -shared -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 

  TARGET := Atmosfear.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/Base64_5afe1247.o \
  $(OBJDIR)/TeragonPluginBase_c8063247.o \
  $(OBJDIR)/tinythread_51467623.o \
  $(OBJDIR)/ImageKnob_234e9ab6.o \
  $(OBJDIR)/ImageSlider_5ceaa0e1.o \
  $(OBJDIR)/IndicatorLight_81b8276c.o \
  $(OBJDIR)/PushButton_85a25391.o \
  $(OBJDIR)/ResourceCache_4d3196d9.o \
  $(OBJDIR)/Resources_244c186a.o \
  $(OBJDIR)/StatusBar_62e48306.o \
  $(OBJDIR)/ThinButton_20dde050.o \
  $(OBJDIR)/Constants_e698e730.o \
  $(OBJDIR)/FileWatcherThread_43704f2b.o \
  $(OBJDIR)/PluginEditor_94d4fb09.o \
  $(OBJDIR)/PluginProcessor_a059e380.o \
  $(OBJDIR)/VoiceController_8625c7cf.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_audio_basics_2442e4ea.o \
  $(OBJDIR)/juce_audio_formats_d349f0c8.o \
  $(OBJDIR)/juce_audio_processors_44a134a2.o \
  $(OBJDIR)/juce_core_aff681cc.o \
  $(OBJDIR)/juce_data_structures_bdd6d488.o \
  $(OBJDIR)/juce_events_79b2840.o \
  $(OBJDIR)/juce_graphics_c8f1e7a4.o \
  $(OBJDIR)/juce_gui_basics_a630dd20.o \
  $(OBJDIR)/juce_gui_extra_7767d6a8.o \
  $(OBJDIR)/juce_PluginUtilities_e2e19a34.o \
  $(OBJDIR)/juce_VST_Wrapper_bb62e93d.o \
  $(OBJDIR)/juce_VST3_Wrapper_77e7c73b.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(RESOURCES)
	@echo Linking Atmosfear
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning Atmosfear
	@$(CLEANCMD)

strip:
	@echo Stripping Atmosfear
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/Base64_5afe1247.o: ../../Third-Party/TeragonGuiComponents/Components/Plugin/arduino-base64/Base64.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Base64.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TeragonPluginBase_c8063247.o: ../../Third-Party/TeragonGuiComponents/Components/Plugin/TeragonPluginBase.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TeragonPluginBase.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/tinythread_51467623.o: ../../Third-Party/TeragonGuiComponents/Components/PluginParameters/include/tinythread/source/tinythread.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling tinythread.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ImageKnob_234e9ab6.o: ../../Third-Party/TeragonGuiComponents/Components/Source/ImageKnob.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ImageKnob.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ImageSlider_5ceaa0e1.o: ../../Third-Party/TeragonGuiComponents/Components/Source/ImageSlider.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ImageSlider.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/IndicatorLight_81b8276c.o: ../../Third-Party/TeragonGuiComponents/Components/Source/IndicatorLight.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling IndicatorLight.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PushButton_85a25391.o: ../../Third-Party/TeragonGuiComponents/Components/Source/PushButton.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PushButton.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ResourceCache_4d3196d9.o: ../../Third-Party/TeragonGuiComponents/Components/Source/ResourceCache.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ResourceCache.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Resources_244c186a.o: ../../Third-Party/TeragonGuiComponents/Components/Source/Resources.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Resources.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/StatusBar_62e48306.o: ../../Third-Party/TeragonGuiComponents/Components/Source/StatusBar.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling StatusBar.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ThinButton_20dde050.o: ../../Third-Party/TeragonGuiComponents/Components/Source/ThinButton.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ThinButton.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Constants_e698e730.o: ../../Source/Constants.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Constants.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FileWatcherThread_43704f2b.o: ../../Source/FileWatcherThread.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FileWatcherThread.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PluginEditor_94d4fb09.o: ../../Source/PluginEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PluginEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PluginProcessor_a059e380.o: ../../Source/PluginProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PluginProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/VoiceController_8625c7cf.o: ../../Source/VoiceController.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling VoiceController.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_2442e4ea.o: ../../JuceLibraryCode/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_d349f0c8.o: ../../JuceLibraryCode/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_44a134a2.o: ../../JuceLibraryCode/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_aff681cc.o: ../../JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_bdd6d488.o: ../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_79b2840.o: ../../JuceLibraryCode/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_c8f1e7a4.o: ../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_a630dd20.o: ../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_7767d6a8.o: ../../JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_PluginUtilities_e2e19a34.o: ../../JuceLibraryCode/modules/juce_audio_plugin_client/utility/juce_PluginUtilities.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_PluginUtilities.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST_Wrapper_bb62e93d.o: ../../JuceLibraryCode/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST3_Wrapper_77e7c73b.o: ../../JuceLibraryCode/modules/juce_audio_plugin_client/VST3/juce_VST3_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST3_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
