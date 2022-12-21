#include <iostream>
#include <cstdint>
#include <fstream>

extern const char* const identifier;
extern const char* const informations;

// class GrayImage : classe représentant une image en niveaux de gris
class GrayImage{ 
    private:
        const uint16_t width, height; // Hauteur et largeur de l'image
        uint8_t *array; // Tableau de pixels en niveaux de gris

    public :
        GrayImage() = delete;
        GrayImage& operator=(const GrayImage& b) = delete;
        GrayImage(uint16_t w, uint16_t h);
        GrayImage(const GrayImage& orig);
        ~GrayImage();

        inline const uint16_t& getWidth() const { return width; }
        inline const uint16_t& getHeight() const { return height; }

        inline uint8_t& pixel(uint16_t x, uint16_t y) { return array[y * width + x]; }
        inline void pixel(uint16_t x, uint16_t y, uint8_t color) { array[y * width + x] = color; }

        void clear(uint8_t color = 0);
        void rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color);
        void fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color);
        void fillCircle(uint16_t x, uint16_t y, uint16_t r, uint8_t color);
        void circle(uint16_t x, uint16_t y, uint16_t r, uint8_t color);
        void line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
        void writePGM(std::ostream&) const;
        static GrayImage* readPGM(std::istream&);
};

// class Color : classe représentant un pixel en couleur
class Color{ 
    private:
        uint8_t r, g, b; // composantes RGB du pixel

    public:
        Color(): r(0), g(0), b(0) {}; 
        Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
        Color(const Color& orig): r(orig.r), g(orig.g), b(orig.b) {}
        Color& operator=(const Color& b); 
        Color& operator*(double d);
        Color& operator+(const Color& b); 
        bool operator==(const Color& a) const; 
        ~Color() = default; 
        
        inline const uint8_t& getR() const { return r; } 
        inline const uint8_t& getG() const { return g; }
        inline const uint8_t& getB() const { return b; }

        inline void setR(uint8_t r) { this->r = r; } 
        inline void setG(uint8_t g) { this->g = g; }
        inline void setB(uint8_t b) { this->b = b; } 
};

// class ColorImage : classe représentant une image en couleur
class ColorImage{ 
    private:
        const uint16_t width, height; // Hauteur et largeur de l'image
        Color *array; // Tableau de pixels en couleur

    public :
        ColorImage() = delete; 
        ColorImage& operator=(const ColorImage& b) = delete; 
        ColorImage(uint16_t w, uint16_t h); 
        ColorImage(const ColorImage& orig); 
        ~ColorImage(); 
 
        inline const uint16_t& getWidth() const { return width; } 
        inline const uint16_t& getHeight() const { return height; } 
 
        inline Color& pixel(uint16_t x, uint16_t y) const { return array[y * width + x]; } 
        inline void pixel(uint16_t x, uint16_t y, Color color) { array[y * width + x] = color; } 
 
        void clear(Color color = Color(0, 0, 0)); 
        void rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const Color& color); 
        void fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const Color& color); 
        void fillCircle(uint16_t x, uint16_t y, uint16_t r, const Color& color); 
        void circle(uint16_t x, uint16_t y, uint16_t r, const Color& color); 
        void line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const Color& color); 
        void writePPM(std::ostream&) const; 
        static ColorImage* readPPM(std::istream&);
        //void ColorImage::writeJPEG(const char *fname) const;
        ColorImage* simpleScale(uint16_t w, uint16_t h) const; 
        ColorImage* bilinearScale(uint16_t w, uint16_t h) const;
        void writeTGA(std::ostream&, bool rle) const;
        static ColorImage* readTGA(std::istream&);
        void reverseimgtga();
        static ColorImage* readMaison3(std::istream& is);
};
