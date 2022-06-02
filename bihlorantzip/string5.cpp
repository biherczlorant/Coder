/**
 *
 * \file string5.cpp
 *
 * Itt kell megvalósítania a hiányzó tagfüggvényeket.
 * Segítségül megadtuk a C++ nem OO eszközeinek felhasználásával készített String-kezelő
 * függvényke neveit.
 *
 * Ha valamit INLINE-ként valósít meg, akkor annak a string5.h-ba kell kerülnie,
 * akár kívül akár osztályon belül definiálja. (Az inline függvényeknek minden
 * fordítási egységben elérhetőknek kell lenniük)
 * *
 * A teszteléskor ne felejtse el beállítani a string5.h állományban az ELKESZULT makrót.
 *
 */

#ifdef _MSC_VER
// MSC ne adjon figyelmeztető üzenetet a C sztringkezelő függvényeire
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>             // Kiíratáshoz
#include <cstring>              // Sztringműveletekhez

#include "memtrace.h"           // a standard headerek után kell lennie
#include "string5.h"


/// Konstruktorok: egy char karakterből (createString)
String::String(const char character) {len = 1; pData = new char[len+1]; pData[0] = character; pData[1] = '\0';}
///                egy nullával lezárt char sorozatból (createString)
String::String(const char *cstring) {len = strlen(cstring); pData = new char[len+1]; strcpy(pData, cstring);}
/// Másoló konstruktor: String-ből készít (createString)
String::String(const String& s) {
    len = s.len;
    if (len != 0) {
        pData = new char[len + 1];
        strcpy(pData, s.pData);
    }else{
        pData = new char[len+1];
        pData[len] = '\0';
    }
}
/// Destruktor (disposeString)
String::~String() {delete[] pData;}
/// operator=
String& String::operator=(const String& s) {
    if(this != &s){
        delete[] pData;
        this->pData = new char[(len = s.len)+1];
        strcpy(this->pData, s.pData);
    }
    return *this;
}
/// [] operátorok: egy megadott indexű elem REFERENCIÁJÁVAL térnek vissza (charAtString)
/// indexhiba esetén const char * kivételt dob!
char& String::operator[](const size_t idx){
    if(idx >= this->len){
        throw "Index error";
    }
    return this->pData[idx];
}

/// + operátorok:
///                 String-hez jobbról karaktert ad (addString)
///                 String-hez String-et ad (addString)
String String::operator+(const char a) const {String nw; nw.len = len+1; nw.pData = new char[nw.len + 1];
    strcpy(nw.pData, pData); nw.pData[nw.len-1] = a; nw.pData[nw.len] = '\0'; return nw;}
String String::operator+(const String& s) const{String nw; nw.len = len + s.len; nw.pData = new char[nw.len + 1];
    strcpy(nw.pData, this->pData);
    strcat(nw.pData, s.pData);
    return nw;}

bool String::operator==(String& s) {
    if(this->size() == s.size()){
        for (size_t i = 0; i < s.size(); ++i) {
            if(s[i] != this->pData[i])
                return false;
            else
                continue;
        }
    }else{
        return false;
    }
    return true;
}

String operator+(const char c, const String& s){
    String nw(c);
    nw = nw + s;
    return nw;

}
/// << operator, ami kiír az ostream-re
std::ostream& operator<<(std::ostream& os, String& s){
    for(size_t i = 0; i < s.size(); i++){
        os << s[i];
    }
    return os;
}

/// >> operátor, ami beolvas az istream-ről egy szót
std::istream& operator>>(std::istream& is, String& s){
    unsigned char ch;
    s = String("");            // üres string, ehhez fűzünk hozzá
    std::ios_base::fmtflags fl = is.flags(); // eltesszük a régi flag-eket
    is.setf(std::ios_base::skipws);			// az elején eldobjuk a ws-t
    while (is >> ch) {
        is.unsetf(std::ios_base::skipws);	// utána pedig már nem
        if (isspace(ch) != 0 && ch != ' '){
            is.putback(ch);             // na ezt nem kérjük
            break;
        } else {
            s = s + ch;               // végére fűzzük a karaktert
        }
    }
    is.setf(fl);						// visszaállítjuk a flag-eket
    return is;
}