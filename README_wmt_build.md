# C++ Native Swing Implementation: Xwing


## How To Build (by weimingtom)  
* Ubuntu Install:  
g++  
sudo apt-get install g++  
libgc  
sudo apt-get install libgc-dev  

* Build and Run:  
$ cd src  
$ make  
$ make demo  
$ ./xwing/frametest  
$ make clean  

## Important place  
* src/awt/Frame.cc  
void Frame::addNotify()  
* src/awt/NativeGraphics.cc  
void NativeGraphics::setFont ( awt::Font* font )  
* src/xwing/frametest.cc  
int main()  
* src/awt/Graphics.cc  
awt::Font* Graphics::SWING_FONT = new awt::Font(new String("6*10"/*"-*-lucida-bold-r-*-*-12-*-*-*-*-*-*-*"*/), 2, 12);  

