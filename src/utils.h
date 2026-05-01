#pragma once

inline const char* getKeyName(const char key) {
    switch (key) {
        case 'e': return "IGNICAO";
        case 'f': return "ALERTA";
        case 'h': return "BUZINA";
        case 'i': return "LIMPADOR -";
        case 'k': return "FAROL ALTO";
        case 'l': return "FAROL";
        case 'm': return "MAPA";
        case 'n': return "BUZINA A AR";
        case 'o': return "GIROFLEX";
        case 'p': return "LIMPADOR +";
        case 't': return "REBOQUE";
        case ']': return "SETA ESQ";
        case '[': return "SETA DIR";
        case ' ': return "FREIO MAO";
        case '+': return "VIDRO +";
        case '-': return "VIDRO -";
        default: return "DESCONHECIDO";
    }
}