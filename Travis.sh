# this script is intended to be run by Travis
# see https://travis-ci.org/avilleret/Gem

if [[ "$TRAVIS_OS_NAME" = "linux" ]]; then
  sudo apt-get install puredata-dev
  ./autogen.sh && ./configure && make
else
	brew install pkg-config gettext
  brew link gettext --force
  brew install imagemagick ftgl
  brew install sdl homebrew/versions/glfw2 homebrew/versions/glfw3

  wget http://msp.ucsd.edu/Software/pd-0.46-2-64bit.mac.tar.gz
  tar -xvf pd-0.46-2-64bit.mac.tar.gz

  ./autogen.sh
  ./configure --with-pd=$(pwd)/Pd-0.46-2-64bit.app/Contents/Resources/ --without-QuickTime-framework --without-Carbon-framework && make
fi
