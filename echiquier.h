#ifndef ECHIQUIER_H
#define ECHIQUIER_H

#include <string>
#include <list>
#include <memory>




using coordonnee = signed int;
enum class couleur { blanc , noir };

class position {
private:
    coordonnee _x;
    coordonnee _y;


public:
    position(coordonnee x, coordonnee y);
    position()= default;
    position(const position &p);
    coordonnee getX()const;
    coordonnee getY()const;
    void setX(coordonnee x);
    void setY(coordonnee y);
    bool operator==(position const &p)const{ return ((p._x ==_x) && (p._y == _y)); }
    bool operator!=(position const &p)const{ return !((p._x ==_x) && (p._y == _y)); }
    void afficherPosition(std::ostream &flux)const;
    bool estValide()const{ return (_x >= 0 && _x < 8 && _y >= 0 && _y < 8);}
    std::string toString() const { return "X=" + std::to_string(_x) + " Y=" + std::to_string(_y); }

};


class piece {
private:
    couleur _couleur;
    position _position;

public:
    ~piece()=default;
    piece(couleur couleur, position position);
    piece(piece const &p) = default;
    position getPosition()const{ return position(_position.getX(), _position.getY());}
    virtual char getSymbole()const =0;
    virtual std::string toString()const;
    virtual std::list<position> deplacementsPossibles(std::list<std::unique_ptr<piece>> const & listePieces)const = 0;
    bool accepterPosition(const position &pos, std::list<std::unique_ptr<piece>> const & listePieces)const;
    couleur getCouleur()const{ return _couleur;}
    bool deplacer(position const &destination, const std::list<std::unique_ptr<piece> > &listePieces);
    virtual std::unique_ptr<piece> clone() const =0;

};


class pion :public piece{
private:

public:
    pion(couleur couleur, position position);
    pion(pion const &p) = default;
    ~pion()=default;
    position getPosition()const { return piece::getPosition(); }
    char getSymbole()const override{ return 'P';};
    std::string toString()const override { return getSymbole() + piece::toString(); }
    std::list<position> deplacementsPossibles(std::list<std::unique_ptr<piece>> const & listePieces)const override;
    std::unique_ptr<piece> clone() const override { return std::make_unique<pion>(*this); }

};

class cavalier :public piece{
private:

public:
    cavalier(couleur couleur, position position);
    cavalier(cavalier const &c) = default;
    ~cavalier()=default;
    position getPosition()const { return piece::getPosition(); }
    char getSymbole()const override { return 'C';};
    std::string toString()const override{ return getSymbole() + piece::toString(); }
    std::list<position> deplacementsPossibles(std::list<std::unique_ptr<piece>> const & listePieces)const override;
    std::unique_ptr<piece> clone() const override { return std::make_unique<cavalier>(*this); }

};



class roi :public piece{
private:

public:
    roi(couleur couleur, position position);
    roi(roi const &r) = default;
    ~roi()=default;
    position getPosition()const { return piece::getPosition(); }
    char getSymbole()const override { return 'R';}
    std::string toString()const override{ return getSymbole() + piece::toString(); }
    std::list<position> deplacementsPossibles(std::list<std::unique_ptr<piece>> const & listePieces)const override;
    std::unique_ptr<piece> clone() const override { return std::make_unique<roi>(*this); }

};


class dame :public piece{
private:

public:
    dame(couleur couleur, position position);
    dame(dame const &d) = default;
    ~dame()=default;
    position getPosition()const { return piece::getPosition(); }
    char getSymbole()const override { return 'D';}
    std::string toString()const override { return getSymbole() + piece::toString(); }
    std::list<position> deplacementsPossibles(std::list<std::unique_ptr<piece>> const & listePieces)const override;
    std::unique_ptr<piece> clone() const override { return std::make_unique<dame>(*this); }

};


class fou :public piece{
private:

public:
    fou(couleur couleur, position position);
    fou(fou const &f) = default;
    ~fou()=default;
    position getPosition()const { return piece::getPosition(); }
    char getSymbole()const override { return 'F';}
    std::string toString()const override { return getSymbole() + piece::toString(); }
    std::list<position> deplacementsPossibles(std::list<std::unique_ptr<piece>> const & listePieces)const override;
    std::unique_ptr<piece> clone() const override { return std::make_unique<fou>(*this); }

};



class tour :public piece{
private:

public:
    tour(couleur couleur, position position);
    tour(tour const &t) = default;
    ~tour()=default;
    position getPosition()const { return piece::getPosition(); }
    char getSymbole()const override { return 'T';}
    std::string toString()const override { return getSymbole() + piece::toString(); }
    std::list<position> deplacementsPossibles(std::list<std::unique_ptr<piece>> const & listePieces)const override;
    std::unique_ptr<piece> clone() const override { return std::make_unique<tour>(*this); }

};

class echiquier {
private:
    std::list<std::unique_ptr<piece>> _ensemblePieces;
    std::list<std::unique_ptr<piece>> _ensemblePrisonniers;

public:
    echiquier()=default;
    ~echiquier()=default;
    void ajouterPiece(std::unique_ptr<piece> p);
    bool deplacer(position const& source, position  const& destination);
    echiquier(echiquier const & ech);
    echiquier operator=(echiquier &ech)const;
    void affichage(std::ostream & flux)const;
    void depart();
    bool roiVivant(couleur const& coul)const;
    bool pieceExiste(position const & pos) const;
    couleur getCouleurPiece(position const & pos) const;
    void transformerPion(couleur const & color,position const & positionTmp);
    couleur roiEnEchec() const;
    void jouer();

};

























#endif // ECHIQUIER_H
