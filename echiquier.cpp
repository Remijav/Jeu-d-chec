#include <iostream>
#include <string>
#include <list>
#include "echiquier.h"
#include <algorithm>



//      POSITION
position::position(coordonnee x, coordonnee y): _x(x), _y(y) {}
position::position(const position &p): _x(p._x), _y(p._y){}
coordonnee position::getX()const{ return _x;}
coordonnee position::getY()const{ return _y;}
void position::setX(coordonnee x){ _x = x;}
void position::setY(coordonnee y){ _y = y;}
void position::afficherPosition(std::ostream &flux)const{ flux << "x=" << getX() << " y=" << getY() << std::endl;}


//      PIECE
piece::piece(couleur couleur, position position): _couleur(couleur),_position(position){}

std::string piece::toString()const{
    char chaine1=' ';
    switch(_couleur){
        case couleur::noir:
        void chargement(std::ifstream & fluxFichier);
            chaine1='N';
            break;
        case couleur::blanc:
            chaine1='B';
            break;
    }
    return chaine1 + std::to_string(_position.getX()) + std::to_string(_position.getY()) + "\n";
}


bool piece::accepterPosition(const position &pos, std::list<std::unique_ptr<piece>> const & listePieces)const{
    for (auto &posTest: deplacementsPossibles(listePieces)){
        if(posTest == pos) return true;
    }
    return false;
}


bool piece::deplacer(position const &destination, std::list<std::unique_ptr<piece>> const & listePieces){
    if(accepterPosition(destination, listePieces)){
        _position.setX(destination.getX());
        _position.setY(destination.getY());
        return true;
    }
    return false;
}


//      PION
pion::pion(couleur couleur, position position): piece(couleur, position) {}

std::list<position> pion::deplacementsPossibles(std::list<std::unique_ptr<piece>> const & listePieces)const{
    std::list<position> listePos;
    position positionTmp1;
    position positionTmp2;
    bool occupe;
    // Cas du joueur noir
    if(piece::getCouleur() == couleur::noir){
        // Si le pion n'a encore jamais été déplacé
        if(piece::getPosition().getY() == 6){
            positionTmp1 = position(piece::getPosition().getX(), piece::getPosition().getY() - 2 );
            positionTmp2 = position(piece::getPosition().getX(), piece::getPosition().getY() - 1 ); // Pour vérifier si aucun pion ne bloque le passage pour ne pas sauter par dessus
            occupe = false;
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTmp1 || elt->getPosition() == positionTmp2){
                    occupe = true;
                    break;
                }
            }
            if(!occupe) listePos.push_back(positionTmp1);
        }
        // S'il a déjà été déplacé
        if(piece::getPosition().getY() >= 0){
            positionTmp1 = position(piece::getPosition().getX(), piece::getPosition().getY() - 1 );
            occupe = false;
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTmp1){
                    occupe = true;
                    break;
                }
            }
            if(!occupe) listePos.push_back(positionTmp1);
        }
        // Si un pion adverse se trouve dans une de ses deux cases diagonales
        positionTmp1 = position(piece::getPosition().getX() -1 , piece::getPosition().getY() - 1 );
        positionTmp2 = position(piece::getPosition().getX() +1 , piece::getPosition().getY() - 1 );

        if(positionTmp1.estValide()){
            for(auto const & elt : listePieces)
                if(elt->getPosition() == positionTmp1) listePos.push_back(positionTmp1);
        }

        if(positionTmp2.estValide()){
            for(auto const & elt : listePieces)
                if(elt->getPosition() == positionTmp2) listePos.push_back(positionTmp2);
        }
    }
//  /////////////////////////////////////////////////
    // Cas du joueur blanc
    else {
        // Si le pion n'a encore jamais été déplacé
        if(piece::getPosition().getY() == 1){
            positionTmp1 = position(piece::getPosition().getX(), piece::getPosition().getY() + 2 );
            positionTmp2 = position(piece::getPosition().getX(), piece::getPosition().getY() + 1 ); // Pour vérifier si aucun pion ne bloque le passage pour ne pas sauter par dessus
            occupe = false;
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTmp1 || elt->getPosition() == positionTmp2){
                    occupe = true;
                    break;
                }
            }
            if(!occupe) listePos.push_back(positionTmp1);
        }
        // S'il a déjà été déplacé
        if(piece::getPosition().getX() <= 7 ){
            positionTmp1 = position(piece::getPosition().getX(), piece::getPosition().getY() + 1 );
            occupe = false;
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTmp1){
                    occupe = true;
                    break;
                }
            }
            if(!occupe) listePos.push_back(positionTmp1);
        }
        // Si un pion adverse se trouve dans une de ses deux cases diagonales
        positionTmp1 = position(piece::getPosition().getX() -1 , piece::getPosition().getY() + 1 );
        positionTmp2 = position(piece::getPosition().getX() +1 , piece::getPosition().getY() + 1 );

        if(positionTmp1.estValide()){
            for(auto const & elt : listePieces)
                if(elt->getPosition() == positionTmp1) listePos.push_back(positionTmp1);
        }

        if(positionTmp2.estValide()){
            for(auto const & elt : listePieces)
                if(elt->getPosition() == positionTmp2) listePos.push_back(positionTmp2);
        }
    }
    return listePos;
}


//      CAVALIER
cavalier::cavalier(couleur couleur, position position): piece(couleur, position) {}
std::list<position> cavalier::deplacementsPossibles(std::list<std::unique_ptr<piece>> const & listePieces)const{
    std::list<position> listePos;
    couleur color = piece::getCouleur();
    bool occupe;
    bool memeCouleur;
    position positionTest;
    coordonnee abscisse = piece::getPosition().getX();
    coordonnee ordonnee = piece::getPosition().getY();

    // Position 1
    positionTest = position(abscisse-2, ordonnee-1);
    if(positionTest.estValide()){
        occupe = false;
        memeCouleur = false;
        for(auto const & elt : listePieces){
            if(elt->getPosition() == positionTest){
                occupe = true;
                if(elt->getCouleur() == color ) memeCouleur = true;
                break;
            }
        }
        if(!occupe) listePos.push_back(positionTest);
        else if(!memeCouleur) listePos.push_back(positionTest);
    }

    // Position 2
    positionTest = position(abscisse-1, ordonnee-2);
    if(positionTest.estValide()){
        occupe = false;
        memeCouleur = false;
        for(auto const & elt : listePieces){
            if(elt->getPosition() == positionTest){
                occupe = true;
                if(elt->getCouleur() == color ) memeCouleur = true;
                break;
            }
        }
        if(!occupe) listePos.push_back(positionTest);
        else if(!memeCouleur) listePos.push_back(positionTest);
    }

    // Position 3
    positionTest = position(abscisse+1, ordonnee-2);
    if(positionTest.estValide()){
        occupe = false;
        memeCouleur = false;
        for(auto const & elt : listePieces){
            if(elt->getPosition() == positionTest){
                occupe = true;
                if(elt->getCouleur() == color ) memeCouleur = true;
                break;
            }
        }
        if(!occupe) listePos.push_back(positionTest);
        else if(!memeCouleur) listePos.push_back(positionTest);
    }

    // Position 4
    positionTest = position(abscisse+2, ordonnee-1);
    if(positionTest.estValide()){
        occupe = false;
        memeCouleur = false;
        for(auto const & elt : listePieces){
            if(elt->getPosition() == positionTest){
                occupe = true;
                if(elt->getCouleur() == color ) memeCouleur = true;
                break;
            }
        }
        if(!occupe) listePos.push_back(positionTest);
        else if(!memeCouleur) listePos.push_back(positionTest);
    }

    // Position 5
    positionTest = position(abscisse-2, ordonnee+1);
    if(positionTest.estValide()){
        occupe = false;
        memeCouleur = false;
        for(auto const & elt : listePieces){
            if(elt->getPosition() == positionTest){
                occupe = true;
                if(elt->getCouleur() == color ) memeCouleur = true;
                break;
            }
        }
        if(!occupe) listePos.push_back(positionTest);
        else if(!memeCouleur) listePos.push_back(positionTest);
    }

    // Position 6
    positionTest = position(abscisse-1, ordonnee+2);
    if(positionTest.estValide()){
        occupe = false;
        memeCouleur = false;
        for(auto const & elt : listePieces){
            if(elt->getPosition() == positionTest){
                occupe = true;
                if(elt->getCouleur() == color ) memeCouleur = true;
                break;
            }
        }
        if(!occupe) listePos.push_back(positionTest);
        else if(!memeCouleur) listePos.push_back(positionTest);
    }

    // Position 7
    positionTest = position(abscisse+1, ordonnee+2);
    if(positionTest.estValide()){
        occupe = false;
        memeCouleur = false;
        for(auto const & elt : listePieces){
            if(elt->getPosition() == positionTest){
                occupe = true;
                if(elt->getCouleur() == color ) memeCouleur = true;
                break;
            }
        }
        if(!occupe) listePos.push_back(positionTest);
        else if(!memeCouleur) listePos.push_back(positionTest);
    }

    // Position 8
    positionTest = position(abscisse+2, ordonnee+1);
    if(positionTest.estValide()){
        occupe = false;
        memeCouleur = false;
        for(auto const & elt : listePieces){
            if(elt->getPosition() == positionTest){
                occupe = true;
                if(elt->getCouleur() == color ) memeCouleur = true;
                break;
            }
        }
        if(!occupe) listePos.push_back(positionTest);
        else if(!memeCouleur) listePos.push_back(positionTest);
    }


    return listePos;
}

//      ROI
roi::roi(couleur couleur, position position): piece(couleur, position) {}

std::list<position> roi::deplacementsPossibles(std::list<std::unique_ptr<piece>> const & listePieces)const{
    std::list<position> listePos;
    couleur color = piece::getCouleur();
    bool occupe;
    bool memeCouleur;
    position positionTest;
    coordonnee abscisse = piece::getPosition().getX();
    coordonnee ordonnee = piece::getPosition().getY();
    for(int i=-1; i<2; i++){
        for(int j=-1; j<2; j++){
            occupe = false;
            memeCouleur = false;
            positionTest = position(abscisse+i,ordonnee+j);
            if(positionTest != piece::getPosition()){
                if(positionTest.estValide()){
                    for(auto const & elt : listePieces){
                        if(elt->getPosition() == positionTest){
                            occupe = true;
                            if(elt->getCouleur() == color) memeCouleur = true;
                        }
                    }
                    if(!occupe) listePos.push_back(positionTest);
                    else if(!memeCouleur) listePos.push_back(positionTest);
                }
            }
        }
    }
    return listePos;
}

//      DAME
dame::dame(couleur couleur, position position): piece(couleur, position) {}

std::list<position> dame::deplacementsPossibles(std::list<std::unique_ptr<piece>> const & listePieces)const{
    std::list<position> listePos;
    couleur color = piece::getCouleur();
    bool occupe;
    bool memeCouleur;
    position positionTest;

// --------------- DIAGONALES
    // Diagonale en haut à gauche
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setX(positionTest.getX()-1);
        positionTest.setY(positionTest.getY()-1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }

    // Diagonale en haut à droite
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setX(positionTest.getX()+1);
        positionTest.setY(positionTest.getY()-1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }

    // Diagonale en bas à gauche
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setX(positionTest.getX()-1);
        positionTest.setY(positionTest.getY()+1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }

    // Diagonale en bas à droite
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setX(positionTest.getX()+1);
        positionTest.setY(positionTest.getY()+1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }

// --------------- COLONNES ET LIGNES
    // Colonne vers le haut
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setY(positionTest.getY()-1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }

    // Colonne vers le bas
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setY(positionTest.getY()+1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }

    // Ligne vers la gauche
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setX(positionTest.getX()-1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }

    // Ligne vers la droite
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setX(positionTest.getX()+1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }



    return listePos;
}

//      FOU
fou::fou(couleur couleur, position position): piece(couleur, position) {}
std::list<position> fou::deplacementsPossibles(std::list<std::unique_ptr<piece>> const & listePieces)const{
    std::list<position> listePos;
    couleur color = piece::getCouleur();
    bool occupe;
    bool memeCouleur;
    position positionTest;

// --------------- DIAGONALES
    // Diagonale en haut à gauche
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setX(positionTest.getX()-1);
        positionTest.setY(positionTest.getY()-1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }

    // Diagonale en haut à droite
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setX(positionTest.getX()+1);
        positionTest.setY(positionTest.getY()-1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }

    // Diagonale en bas à gauche
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setX(positionTest.getX()-1);
        positionTest.setY(positionTest.getY()+1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }

    // Diagonale en bas à droite
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setX(positionTest.getX()+1);
        positionTest.setY(positionTest.getY()+1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }
    return listePos;
}


//      TOUR
tour::tour(couleur couleur, position position): piece(couleur, position) {}
std::list<position> tour::deplacementsPossibles(std::list<std::unique_ptr<piece>> const & listePieces)const{
    std::list<position> listePos;
    couleur color = piece::getCouleur();
    bool occupe;
    bool memeCouleur;
    position positionTest;

    // Colonne vers le haut
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setY(positionTest.getY()-1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }

    // Colonne vers le bas
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setY(positionTest.getY()+1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }

    // Ligne vers la gauche
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setX(positionTest.getX()-1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }

    // Ligne vers la droite
    occupe = false;
    memeCouleur = false;
    positionTest = piece::getPosition();
    while(!occupe){
        positionTest.setX(positionTest.getX()+1);
        if(positionTest.estValide()){
            for(auto const & elt : listePieces){
                if(elt->getPosition() == positionTest){
                    occupe = true;
                    if(elt->getCouleur() == color) memeCouleur = true;
                    break;
                }
            } if(!memeCouleur) listePos.push_back(positionTest);
        }
        else occupe = true;
    }

    return listePos;
}


//      ECHIQUIER
void echiquier::ajouterPiece(std::unique_ptr<piece> p){
    _ensemblePieces.push_back(std::move(p));
}

bool echiquier::deplacer(position const& source, position  const& destination){
    if(source.estValide() && destination.estValide()){
        for(auto & src : _ensemblePieces){
            if(src->getPosition() == source){
                for(auto & dest : _ensemblePieces){
                    if(dest->getPosition() == destination){
                        if(src->getCouleur() == dest->getCouleur()) return false;
                        else {
                            src->deplacer(destination, _ensemblePieces);
                            _ensemblePrisonniers.push_back(std::move(dest));
                            _ensemblePieces.remove(dest);
                            return true;
                        }
                    }
                }
                src->deplacer(destination, _ensemblePieces);
                return true;
            }
        }
    }
    return false;
}

echiquier::echiquier(echiquier const & ech){
    for(auto const & piec : ech._ensemblePieces)
        _ensemblePieces.push_back(piec->clone());
}

echiquier echiquier::operator=(echiquier &ech)const{
    ech._ensemblePieces.clear();
    for(auto const & piec : _ensemblePieces)
        ech._ensemblePieces.push_back(piec->clone());
    return ech;
}

void echiquier::affichage(std::ostream & flux)const{
    bool caseOccupee = false;
    flux << " ";
    for(unsigned int i = 0 ; i < 8 ; i++) flux << "| " << i;
    flux << "|" << std::endl;
    for(unsigned int i = 0; i < 8 ; i++){
        flux << i << "|";
        for(unsigned int j = 0; j < 8 ; j++){
            for(auto const & piec: _ensemblePieces){
                if(piec->getPosition() == position(j,i)){
                    caseOccupee = true;

                    flux << piec->getSymbole();
                    if(piec->getCouleur() == couleur::blanc) flux << "B";
                    else flux << "N";
                    flux << "|";
                }
            }
            if(!caseOccupee) flux << "  |";
            caseOccupee = false;
        }
        flux << std::endl;
    }
    flux << std::endl << std::endl;
}



void echiquier::depart(){
    for(unsigned int i = 0; i < 8 ; i++){
        ajouterPiece(std::make_unique<pion>(couleur::blanc, position(i,1)));
        ajouterPiece(std::make_unique<pion>(couleur::noir, position(i,6)));
    }
    ajouterPiece(std::make_unique<cavalier>(couleur::blanc, position(1,0)));
    ajouterPiece(std::make_unique<cavalier>(couleur::blanc, position(6,0)));
    ajouterPiece(std::make_unique<cavalier>(couleur::noir, position(1,7)));
    ajouterPiece(std::make_unique<cavalier>(couleur::noir, position(6,7)));
    ajouterPiece(std::make_unique<roi>(couleur::blanc, position(4,0)));
    ajouterPiece(std::make_unique<roi>(couleur::noir, position(4,7)));
    ajouterPiece(std::make_unique<dame>(couleur::blanc, position(3,0)));
    ajouterPiece(std::make_unique<dame>(couleur::noir, position(3,7)));
    ajouterPiece(std::make_unique<tour>(couleur::noir, position(0,7)));
    ajouterPiece(std::make_unique<tour>(couleur::noir, position(7,7)));
    ajouterPiece(std::make_unique<tour>(couleur::blanc, position(0,0)));
    ajouterPiece(std::make_unique<tour>(couleur::blanc, position(7,0)));
    ajouterPiece(std::make_unique<fou>(couleur::noir, position(2,7)));
    ajouterPiece(std::make_unique<fou>(couleur::noir, position(5,7)));
    ajouterPiece(std::make_unique<fou>(couleur::blanc, position(2,0)));
    ajouterPiece(std::make_unique<fou>(couleur::blanc, position(5,0)));
}

bool echiquier::roiVivant(const couleur &coul)const{
    for(auto const & piec : _ensemblePieces)
        if(piec->getSymbole() == 'R' && piec->getCouleur() == coul) return true;
    return false;
}

bool echiquier::pieceExiste(position const & pos)const{
    for(auto const & piec : _ensemblePieces)
        if(piec->getPosition() == pos) return true;
    return false;
}

couleur echiquier::getCouleurPiece(position const & pos) const{
    for(auto const & piec : _ensemblePieces)
        if(piec->getPosition() == pos) return piec->getCouleur();
    return couleur::blanc;
}

void echiquier::transformerPion(couleur const & color,position const & positionTmp){
    char symbole=' ';
    while(symbole != 'D' && symbole != 'T' && symbole != 'C' && symbole != 'F'){
        std::cout << "Transformer le pion en Dame 'D', en tour 'T', en Cavalier 'C', en Fou 'F' : " << std::endl;
        std::cin >> symbole;
    }

    std::list<std::unique_ptr<piece>>::iterator it = _ensemblePieces.begin();
    while(it != _ensemblePieces.end()){
        if(it->get()->getPosition() == positionTmp){
            std::list<std::unique_ptr<piece>>::iterator itTmp = it;
            _ensemblePrisonniers.push_back(std::move(*it));
            _ensemblePieces.remove(*itTmp);
        }
        ++it;
    }

    switch (symbole) {
        case 'D':
            ajouterPiece(std::make_unique<dame>(color, positionTmp));
            break ;

        case 'T':
            ajouterPiece(std::make_unique<tour>(color, positionTmp));
            break ;

        case 'C':
            ajouterPiece(std::make_unique<cavalier>(color, positionTmp));
            break ;

        case 'F':
            ajouterPiece(std::make_unique<fou>(color, positionTmp));
            break ;
    }
}

/*
couleur echiquier::roiEnEchec() const{
    position positionRoiBlanc, positionRoiNoir;
    couleur color;
    for(auto const & elt : _ensemblePieces){
        if(elt->getSymbole() == 'R' && elt->getCouleur() == couleur::blanc) positionRoiBlanc = elt->getPosition();
        if(elt->getSymbole() == 'R' && elt->getCouleur() == couleur::noir) positionRoiNoir = elt->getPosition();
    }

    for(auto const & elt : _ensemblePieces){
        if(elt->getCouleur() == couleur::blanc){
            for(auto const & pos : elt->deplacementsPossibles(_ensemblePieces)){
                if(pos == positionRoiNoir) color = couleur::noir;
            }
        }
        if(elt->getCouleur() == couleur::noir){
            for(auto const & pos : elt->deplacementsPossibles(_ensemblePieces)){
                if(pos == positionRoiBlanc) color = couleur::blanc;
            }
        }
    }
    return color;
}*/


void echiquier::jouer(){
    couleur color = couleur::blanc;
    while(roiVivant(couleur::blanc) && roiVivant(couleur::noir)){
        int x,y,a,b;
        bool estUnPion = false;
        std::list<position> positionsPossibles;
        position positionTmp1;
        position positionTmp2;
        if(color == couleur::blanc) std::cout << "Tour du joueur blanc.\n";
        else std::cout << "Tour du joueur noir.\n";

    //    if(roiEnEchec() == couleur::blanc) std::cout << "Roi blanc en echec" << std::endl;
    //    if(roiEnEchec() == couleur::noir) std::cout << "Roi noir en echec" << std::endl;

        while(positionsPossibles.empty()){
            do {
                std::cout << "Entrer la position d'une piece : " << std::endl << "X = ";
                std::cin >> x;
                std::cout << "Y = ";
                std::cin >> y;
            }
            while (!position(x,y).estValide() || !pieceExiste(position(x,y)) || color != getCouleurPiece(position(x,y)));
            positionTmp1 = position(x,y);

            std::list<std::unique_ptr<piece>>::iterator it = _ensemblePieces.begin();

            while(it != _ensemblePieces.end()){
                if(it->get()->getPosition() == positionTmp1){
                    if(it->get()->getSymbole() == 'P') estUnPion = true;
                    std::cout << "Piece choisie : " << it->get()->toString() << std::endl;
                    positionsPossibles = it->get()->deplacementsPossibles(_ensemblePieces);
                    break;
                }
                ++it;
            }
            if(positionsPossibles.empty()) std::cout << "Aucun deplacement possible pour cette piece." << std::endl;
        }

        std::cout << "Liste des deplacements possibles : " << std::endl;
        for(auto const & elt : positionsPossibles)
            std::cout << elt.toString() << std::endl;


        bool deplacementValide = false;
        while(!deplacementValide){
            std::cout << "Entrer la nouvelle position de la piece : " << std::endl << "X = ";
            std::cin >> a;
            std::cout << "Y = ";
            std::cin >> b;
            positionTmp2 = position(a,b);

            for(auto const & pos : positionsPossibles){
                if(positionTmp2 == pos) deplacementValide = true;
            }
        }
        deplacer(positionTmp1,positionTmp2);

        if(estUnPion)
            if(positionTmp2.getY() == 0 || positionTmp2.getY() == 7) transformerPion(color,positionTmp2);
        affichage(std::cout);



        std::cout << "Prisonniers :" << std::endl;
        for(auto const & elt : _ensemblePrisonniers){
            std::cout << elt->toString();
        }
        std::cout << std::endl;

        if(color == couleur::noir) color = couleur::blanc;
        else color = couleur::noir;


    }


    if(color == couleur::blanc) std::cout << "Noir gagne.\n" << std::endl;
    else std::cout << "Blanc gagne.\n";

    std::cout << "Fin de la partie." << std::endl;
}




