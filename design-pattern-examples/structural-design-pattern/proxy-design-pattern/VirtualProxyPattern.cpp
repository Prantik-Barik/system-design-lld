/* Virtual Proxy: Defers creation of the real object until it’s actually needed (lazy loading). */
#include<iostream>
#include <string>
using namespace std;

//abstract class
class Image {
    public:
        virtual ~Image() = default;
        virtual void display() = 0;
        virtual string getFileName() = 0;
};

class HighResolutionImage : public Image {
    string filename;
    public:
        HighResolutionImage(string file) {
            this->filename = file;
            // Performs Heavy Operation - 
            cout << "[RealImage] Loading image from disk: " << filename << "\n";
        }

        void display() override {
            cout << "[RealImage] Displaying " << filename << "\n";
        }

        string getFileName() override{
            return filename;
        }
};

// Proxy for lazy loading - loads when and only when it is needed
class ImageProxy : public Image {
    string fileName;
    HighResolutionImage *hsImage;
    public:
        ImageProxy(string fileName) {
            this->fileName = fileName;
            
            //assign null until the display is called, as it is a heavy operation.
            this->hsImage = nullptr;
            
            cout << "ImageProxy: Created for " << fileName << ". Real High Resolution image not loaded yet." << endl;
        }

        ~ImageProxy() {
            delete hsImage;
        }

        string getFileName() override {
            return fileName;
        }

        void display() override {
            if (hsImage == nullptr) {
                cout << "ImageProxy: display() requested for " << fileName << ". Loading high-resolution image..." << endl;
                // Lazy initialization of High Res Real Image
                hsImage = new HighResolutionImage(fileName);
            } else {
                cout << "ImageProxy: Using cached high-resolution image for " << fileName << endl;
            }
            hsImage->display();
        }
};

int main(){
    cout << "Application Started. Initializing image proxies for gallery..." << endl;

    Image* image1 = new ImageProxy("photo1.jpg");
    Image* image2 = new ImageProxy("photo2.png");
    Image* image3 = new ImageProxy("photo3.gif");

    cout << "\nGallery initialized. No images actually loaded yet." << endl;
    cout << "Image 1 Filename: " << image1->getFileName() << endl;

    cout << "\nUser requests to display " << image1->getFileName() << endl;
    image1->display();

    cout << "\nUser requests to display " << image1->getFileName() << " again." << endl;
    image1->display();

    cout << "\nUser requests to display " << image3->getFileName() << endl;
    image3->display();

    cout << "\nApplication finished. Note: photo2.png was never loaded." << endl;

    delete image1;
    delete image2;
    delete image3;
    return 0;
}
