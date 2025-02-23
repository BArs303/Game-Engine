
run:
	cmake --build build/
build:
	cmake -S . -B build -D GLFW_BUILD_WAYLAND=1 -D GLFW_BUILD_X11=0

clean:
	@rm -rf build/*
