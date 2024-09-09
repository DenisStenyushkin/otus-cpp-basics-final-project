# update system
apt-get update
apt-get upgrade -y

# install Linux tools and Python 3
apt-get update -qq && apt-get -y install software-properties-common wget curl \
    python3-dev python3-pip python3-wheel python3-setuptools \
    libavcodec-dev libavformat-dev libavutil-dev libswscale-dev

apt-get update -qq && apt-get -y install \
  autoconf \
  automake \
  build-essential \
  cmake \
  git-core \
  libass-dev \
  libfreetype6-dev \
  libgnutls28-dev \
  libmp3lame-dev \
  libsdl2-dev \
  libtool \
  libva-dev \
  libvdpau-dev \
  libvorbis-dev \
  libxcb1-dev \
  libxcb-shm0-dev \
  libxcb-xfixes0-dev \
  meson \
  ninja-build \
  pkg-config \
  texinfo \
  wget \
  yasm \
  zlib1g-dev \
  nasm \
  libx264-dev \
  libx265-dev \
  libnuma-dev \
  libvpx-dev \
  libfdk-aac-dev \
  libopus-dev \
  libdav1d-dev \
  libgtk2.0-dev \
  libcanberra-gtk-module

# update CUDA Linux GPG repository key
wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/x86_64/cuda-keyring_1.0-1_all.deb
dpkg -i cuda-keyring_1.0-1_all.deb
rm cuda-keyring_1.0-1_all.deb

# install cuDNN
wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/x86_64/cuda-ubuntu2204.pin
mv cuda-ubuntu2204.pin /etc/apt/preferences.d/cuda-repository-pin-600
apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/x86_64/3bf863cc.pub
add-apt-repository "deb https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/x86_64/ /" -y
apt-get update
apt-get install libcudnn8=8.9.0.*-1+cuda12.1
apt-get install libcudnn8-dev=8.9.0.*-1+cuda12.1

# install recommended packages
apt-get install zlib1g g++ git freeglut3-dev \
    libx11-dev libxmu-dev libxi-dev libglu1-mesa libglu1-mesa-dev libfreeimage-dev \ 
    # pkg-config ffmpeg libavformat-dev libavcodec-dev libswscale-dev \ 
    -y

apt install -y cmake make unzip

# Install OpenCV
cd ~
wget -O opencv.zip https://github.com/opencv/opencv/archive/refs/tags/4.10.0.zip
unzip opencv.zip
mv opencv-4.10.0 opencv

wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/refs/tags/4.10.0.zip
unzip opencv_contrib.zip
mv opencv_contrib-4.10.0 opencv_contrib

cd opencv/
mkdir -p build/ && cd build/
cmake -D WITH_FFMPEG=ON \
      -D WITH_CUDA=ON \
      -D WITH_CUDNN=ON \
      -D OPENCV_DNN_CUDA=ON \
      -D CUDA_ARCH_BIN=7.5 \
      -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
      ..
make -j4
make install

# install Python packages
# python3 -m pip install --upgrade pip
# pip3 install --user -r /workspaces/otus-cpp-basics-final-project/.devcontainer/requirements.txt

# clean up
pip3 cache purge
apt-get autoremove -y
apt-get clean
