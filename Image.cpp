#include "Image.hpp"

const char* const identifier = "serre_l";
const char* const informations =  "Je n'ai pas fait de bonus.\n"
                                  "J'ai cependant tenter de faire l'algo de Brensenham pour les lignes,\n"
                                  "il y avait encore des erreurs alors je ne l'ai pas rendu\n"
                                  "Les seules chose que j'ai réaliser en plus sont des fonctions\n"
                                  "qui n'on rien a voir dans les TP pour dessiner des cercles et des lignes.\n"
                                  "J'ai réusssi la premiere partie avec simplest.ma3, je suis rester bloquer de manière\n"
                                  "peut intelligente et je n'ai donc pas eu le temps de faire la partie avec les primitives\n";

// Constructeur de la classe GrayImage
GrayImage::GrayImage(uint16_t w, uint16_t h) 
    : width(w), height(h), array(nullptr) { 
    array = new uint8_t[width * height]; 
}

// Constructeur de copie de la classe GrayImage
GrayImage::GrayImage(const GrayImage& o) 
    : width(o.width), height(o.height), array(nullptr) {
    array = new uint8_t[o.width * o.height];
    for (uint16_t i = 0; i < uint16_t(width * height); i++) 
        array[i] = o.array[i]; 
}

// Destructeur de la classe GrayImage
GrayImage::~GrayImage() { 
    delete[] array;
}

void GrayImage::clear(uint8_t color) { 
    for (uint16_t i = 0; i < uint16_t(width * height); i++) 
        array[i] = color;
}

 // Dessine un rectangle dans une image en niveau de gris
void GrayImage::rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color) {
    for (uint16_t i = x; i < x+w; i++){ // Dessine les lignes horizontales
        pixel(i, y, color);
        pixel(i, y+h, color);
    }
    for (uint16_t j = y; j < y+h; j++){ // Dessine les lignes verticales
        pixel(x, j, color);
        pixel(x+w, j, color);
    }
}

// Dessine un rectangle plein dans une image en niveau de gris
void GrayImage::fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color) { 
    for (uint16_t i = x; i < x+w; i++) { // Parcourt les lignes horizontales
        for (uint16_t j = y; j < y+h; j++) { // Parcourt les lignes verticales
            pixel(i, j, color); // Remplit le rectangle
        }
    }
}

// Ecriture d'une image en niveau de gris
void GrayImage::writePGM(std::ostream& out) const { 
    out << "P5\n#Image sauvegardée par SERRE Loïc pour les TP de RedCod.\n" // Ecriture de l'entête
        << width << " " << height << "\n255\n"; 
    out.write((const char*)array, (width * height));
}

// skip une ligne dans un fichier PGM
static void skip_line(std::istream& is) { 
    char a; // Variable temporaire pour stocker les caractères
    do { 
        a = is.get(); 
    } while (a != '\n'); // tant que le caractère n'est pas un retour à la ligne on continue de lire 
}

// skip les commentaires dans un fichier PGM
static void skip_comment(std::istream& is){ 
    while (is.peek() == '#') skip_line(is); // tant que le caractère suivant est un # on skip la ligne
}

// Lecture d'une image en niveau de gris
GrayImage* GrayImage::readPGM(std::istream& in) {
    char a, b;
    in.get(a); 
    in.get(b);
    if (a != 'P' || b != '5') throw std::runtime_error("L'image n'est pas au format PGM !");
    skip_line(in);
    skip_comment(in);
    uint16_t width, height; // Variables pour stocker la largeur et la hauteur de l'image
    in >> width >> height;
    skip_line(in);
    skip_comment(in);
    skip_line(in);
    GrayImage* img = new GrayImage(width, height); // Création d'une nouvelle image de taille width x height
    in.read((char*)&img->array[0], (width * height)); 
    return img;
}

// Surcharge de l'opérateur pour l'interpolation bilinéaire
Color& Color::operator=(const Color& o) {
    r = o.r;
    g = o.g;
    b = o.b;
    return *this;
}

// Surcharge de l'opérateur pour l'interpolation bilinéaire
Color& Color::operator*(const double f) {
    r = uint8_t(r * f);
    g = uint8_t(g * f);
    b = uint8_t(b * f);
    return *this;
}

// Surcharge de l'opérateur pour l'interpolation bilinéaire
Color& Color::operator+(const Color& o) {
    r = uint8_t(r + o.r);
    g = uint8_t(g + o.g);
    b = uint8_t(b + o.b);
    return *this;
}

//opérateur de comparaison pour la compression RLE
bool Color::operator==(const Color &o) const {
    if (r == o.r && g == o.g && b == o.b)
        return true;
    else
        return false;
}

// Constructeur de la classe ColorImage
ColorImage::ColorImage(uint16_t w, uint16_t h)
    : width(w), height(h), array(nullptr) {
    array = new Color[width * height];
}

// Constructeur de copie de la classe ColorImage
ColorImage::ColorImage(const ColorImage& o)
    : width(o.width), height(o.height), array(nullptr) {
    array = new Color[o.width * o.height];
    for (uint16_t i = 0; i < uint16_t(width * height); i++)
        array[i] = o.array[i];
}

// Destructeur de la classe ColorImage
ColorImage::~ColorImage() {
    delete[] array;
}

void ColorImage::clear(const Color color) {
    for (uint16_t i = 0; i < uint16_t(width * height); i++)
        array[i] = color;
}

// Dessine un rectangle dans une image en couleur
void ColorImage::rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const Color& color) { 
    for (uint16_t i = x; i < x+w; i++){ // Parcourt les lignes horizontales
        pixel(i, y, color);
        pixel(i, y+h, color);
    }
    for (uint16_t j = y; j < y+h; j++){ // Parcourt les lignes verticales
        pixel(x, j, color);
        pixel(x+w, j, color);
    }
}

// Dessine un rectangle plein dans une image en couleur
void ColorImage::fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const Color& color) {
    for (uint16_t i = x; i < x+w; i++) { // Parcourt les lignes horizontales
        for (uint16_t j = y; j < y+h; j++) { // Parcourt les lignes verticales
            pixel(i, j, color); // Remplissage du rectangle
        }
    }
}

// Ecrit une image en couleur au format PPM
void ColorImage::writePPM(std::ostream& out) const {
    out << "P6\n#Image sauvegardée par \"SERRE Loïc\" pour les TP de RedCod.\n"
        << width << " " << height << "\n255\n";
    out.write((const char*)array, (width * height) * 3); // Ecriture de l'image dans le fichier avec son header
}

// Lecture d'une image en couleur au format PPM
ColorImage* ColorImage::readPPM(std::istream& in) {
    char a, b;
    in.get(a);
    in.get(b);
    if (a != 'P' || b != '6') throw std::runtime_error("L'image n'est pas au format PPM !"); 
    skip_line(in);
    skip_comment(in);
    uint16_t width, height; // Variables pour stocker la largeur et la hauteur de l'image
    in >> width >> height;
    skip_line(in);
    skip_comment(in);
    skip_line(in);
    ColorImage* img = new ColorImage(width, height); // Création d'une nouvelle image de taille width x height
    in.read((char*)&img->array[0], (width * height) * 3); // Lecture de l'image dans le fichier
    return img;
}

// Redimensionnement d'une image en couleur avec l'interpolation linéaire
ColorImage* ColorImage::simpleScale(uint16_t w, uint16_t h) const { 
    ColorImage* img = new ColorImage(w, h); // Création d'une nouvelle image de taille w x h
    for(uint16_t j = 0; j < h; j++){ // Parcourt des pixels de l'image
        for(uint16_t i = 0; i < w; i++)
            img->pixel(i, j, pixel(i * width / w, j * height / h)); // Remplissage de l'image avec les pixels de l'image originale redimensionnés
    }
    return img;
}

// Redimensionnement d'une image en couleur avec l'interpolation bilinéaire
ColorImage* ColorImage::bilinearScale(uint16_t w, uint16_t h) const { 
    ColorImage* img = new ColorImage(w, h); // Création d'une nouvelle image de taille w x h
    for (uint16_t i = 0; i < w; i++) { // Parcourt des pixels de l'image
        for (uint16_t j = 0; j < h; j++) { 
            double x = i * width / (double)w; // Calcul des coordonnées du pixel
            double y = j * height / (double)h; 
            uint16_t x1 = (uint16_t)x; // Calcul des coordonnées des pixels voisins
            uint16_t y1 = (uint16_t)y; 
            uint16_t x2 = (x1+1 < width) ? x1+1 : x1; 
            uint16_t y2 = (y1+1 < height) ? y1+1 : y1; 
            double a = x - x1; 
            double b = y - y1;
            Color c1 = pixel(x1, y1); // Calcul des couleurs des pixels voisins
            Color c2 = pixel(x2, y1);
            Color c3 = pixel(x1, y2);
            Color c4 = pixel(x2, y2);
            Color c = c1 * (1-a) * (1-b) + c2 * a * (1-b) + c3 * (1-a) * b + c4 * a * b; // Calcul de la couleur du nouveau pixel
            img->pixel(i, j, c); // Remplissage du pixel
        }
    }
    return img;
}

// dessine un cercle dans une image en couleur, ces fonctions ne sont pas entierement de moi elles ont étais faites juste pour s'amuser
void ColorImage::fillCircle(uint16_t x, uint16_t y, uint16_t r, const Color& color) {
    for (uint16_t i = x-r; i < x+r; i++) { 
        for (uint16_t j = y-r; j < y+r; j++) {
            if ((i-x)*(i-x) + (j-y)*(j-y) <= r*r)
                pixel(i, j, color);
        }
    }
}

void GrayImage::fillCircle(uint16_t x, uint16_t y, uint16_t r, uint8_t color) {
    for (uint16_t i = x-r; i < x+r; i++) { // x-r et x+r pour éviter de faire des calculs inutiles
        for (uint16_t j = y-r; j < y+r; j++) { 
            if ((i-x)*(i-x) + (j-y)*(j-y) <= r*r) // si le point est dans le cercle
                pixel(i, j, color);
        }
    }
}

void GrayImage::circle(uint16_t x, uint16_t y, uint16_t r, uint8_t color) {
    for (uint16_t i = x-r; i < x+r; i++) {
        for (uint16_t j = y-r; j < y+r; j++) {
            if ((i-x)*(i-x) + (j-y)*(j-y) <= r*r && (i-x)*(i-x) + (j-y)*(j-y) >= (r-1)*(r-1))
                pixel(i, j, color);
        }
    }
}

void ColorImage::circle(uint16_t x, uint16_t y, uint16_t r, const Color& color) {
    for (uint16_t i = x-r; i < x+r; i++) {
        for (uint16_t j = y-r; j < y+r; j++) {
            if ((i-x)*(i-x) + (j-y)*(j-y) <= r*r && (i-x)*(i-x) + (j-y)*(j-y) >= (r-1)*(r-1))
                pixel(i, j, color);
        }
    }
}

void GrayImage::line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color) {
    if (x1 == x2) {
        for (uint16_t i = y1; i < y2; i++) {
            pixel(x1, i, color);
        }
    } else {
        double a = (y2-y1)/(double)(x2-x1);
        double b = y1 - a * x1;
        for (uint16_t i = x1; i < x2; i++) {
            pixel(i, a*i+b, color);
        }
    }
}

void ColorImage::line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const Color& color) {
    if (x1 == x2) {
        for (uint16_t i = y1; i < y2; i++) {
            pixel(x1, i, color);
        }
    } else {
        double a = (y2-y1)/(double)(x2-x1);
        double b = y1 - a * x1;
        for (uint16_t i = x1; i < x2; i++) {
            pixel(i, a*i+b, color);
        }
    }
}

// Ecrit le header d'un fichier TGA
void ColorImage::writeTGA(std::ostream& out, bool rle) const {
    out.put(0); // ID length
    out.put(0); // color map type
    if(!rle){ // si on ne veut pas utiliser le RLE
        out.put(2); // image type
        for(int i = 0; i < 9; i++) out.put(0); // color map specification
        out.put(width & 255); out.put((width >> 8) & 255); // ecrit la largeur de l'image en little endian
        out.put(height & 255); out.put((height >> 8) & 255); // ecrit la hauteur de l'image en little endian
        out.put(24); // bits per pixel
        out.put(32); // image descriptor
        out.write((const char *)array, width * height * 3);
    }
    else{ // si on veut utiliser le RLE
        out.put(10); // image type
        for(int i = 0; i < 9; i++) out.put(0); // color map specification
        out.put(width & 255); out.put((width >> 8) & 255); // width
        out.put(height & 255); out.put((height >> 8) & 255); // height
        out.put(24); // bits per pixel
        out.put(32); // image descriptor
        uint32_t count; // compteur du nombre de pixels identiques
        for (uint32_t i = 0; i < width * height; i++){ // on parcoure l'image
            count = 1; // on initialise le compteur à 1 à chaque boucle
            while(i + count < width * height && array[i] == array[i+count] && count < 128) count++; // on compte le nombre de pixels identiques
            if(count > 1){ // si on a plus d'un pixel identique
                out.put(128 + count - 1); // on écrit le nombre de pixels identiques et les couleurs 
                out.put(array[i].getR());
                out.put(array[i].getG());
                out.put(array[i].getB());
                i += count - 1;
            }
            else{ // si on a un pixel unique
                out.put(0); 
                out.put(array[i].getR());
                out.put(array[i].getG());
                out.put(array[i].getB());
            }
        }
    }
}

// retourne une image lue dans un fichier TGA
void ColorImage::reverseimgtga(){
    for (uint32_t i = 0; i < height/2; i++) { // on parcourt la moitié de l'image en hauteur
        for (uint32_t j = 0; j < width; j++) { 
            Color tmp = pixel(j, i); // on stocke la couleur du pixel en haut
            pixel(j, i, pixel(j, height-i-1)); // on remplace la couleur du pixel en haut par celle du pixel en bas
            pixel(j, height-i-1, tmp); // on remplace la couleur du pixel en bas par celle du pixel en haut
        }
    }
}

// lit une image TGA en type 1 ou 2
ColorImage* ColorImage::readTGA(std::istream& in) {
    uint16_t width, height, mapsize; // width et height de l'image, mapsize de la palette
    char c;
    in.get(c);
    in.get(c);
    in.get(c);
    if ((uint8_t)c != 2 && (uint8_t)c != 1) throw std::runtime_error("L'image n'est pas un TGA de type 1 ou 2 !");
    
    if((uint8_t)c == 2){ // si l'image est de type 2
        for (int i = 0; i < 9; i++) in.get(c); // on saute les 9 premiers octets car inutiles
        in.get(c); 
        width = (uint8_t)c; // on lit la largeur de l'image
        in.get(c);
        width += (uint8_t)c * 256; 
        in.get(c);
        height = (uint8_t)c; // on lit la hauteur de l'image
        in.get(c);
        height += (uint8_t)c * 256;
    }
    else if((uint8_t)c == 1){ // si l'image est de type 1
        in.get(c);
        in.get(c);
        in.get(c);
        mapsize = (uint8_t)c;
        in.get(c);
        mapsize += (uint8_t)c * 256;
        in.get(c);
        if ((uint8_t)c != 24) throw std::runtime_error("Les pixels de la palette ne sont pas en 24 bits !");
        for (int i = 0; i < 5; i++) 
            in.get(c);
        width = (uint8_t)c;
        in.get(c);
        width += (uint8_t)c * 256;
        in.get(c);
        height = (uint8_t)c;
        in.get(c);
        height += (uint8_t)c * 256;
        in.get(c);
        in.get(c);
        char origin = c;
        Color* map = new Color[mapsize];
        in.read((char *)&map[0], mapsize * 3);

        ColorImage* img = new ColorImage(width, height);
        for (int i = 0; i < width * height; i++) {
            in.get(c);
            img->array[i] = map[(uint8_t)c];
        }
        if (origin == 0) img->reverseimgtga();
        return img;
    }
    
    in.get(c);
    if (c != 24) throw std::runtime_error("Il n'y a pas 24 bits par pixel !");
    in.get(c);
    ColorImage* img = new ColorImage(width, height);
    in.read((char *)&img->array[0], width * height * 3);
    return img;
}

ColorImage* ColorImage::readMaison3(std::istream& is){
    char header[7];
    uint8_t palettesize;
    uint8_t indcouleurfond;
    uint8_t palette;
    for (int i = 0; i < 7; i++) is.get(header[i]);
    std::string header_str(header, 7);
    if (header_str != "Maison3") throw std::runtime_error("L'image n'est pas au format maison3 !");
    uint16_t height, width;
    char c;
    is.get(c);
    height = (uint8_t)c;
    is.get(c);
    height += (uint8_t)c * 256;
    is.get(c);
    width = (uint8_t)c;
    is.get(c);
    width += (uint8_t)c * 256;
    skip_comment(is);
    is.get(c);
    palettesize = (uint8_t)c;
    char palettecolor[palettesize][3];
    for (int i = 0; i < palettesize; i++) {
        is.get(c);
        palettecolor[i][0] = c;
        is.get(c);
        palettecolor[i][1] = c;
        is.get(c);
        palettecolor[i][2] = c;
    }
    is.get(c);
    indcouleurfond = (uint8_t)c;
    is.get(c);

    //primitive, pas eu le temps

    ColorImage* img = new ColorImage(width, height);
    for (int i = 0; i < width * height; i++) {
        is.get(c);
        img->array[i] = Color(palettecolor[(uint8_t)c][1], palettecolor[(uint8_t)c][0], palettecolor[(uint8_t)c][2]);
    }
    is.read((char *)&img->array[0], width * height * 3);
    return img;
}
