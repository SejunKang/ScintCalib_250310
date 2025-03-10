#ifndef BEAM_HH
#define BEAM_HH

extern const G4int dist;

inline void beam(G4int &cut) {

if (dist == 10) {
    cut = 30;
}
else if (dist == 20) {
    cut = 20;
}
else if (dist == 30) {
    cut = 10;
}
else if (dist == 40) {
    cut = 10;
}
else if (dist == 50) {
    cut = 10;
}
else if (dist == 60) {
    cut = 10;
}
else if (dist == 70) {
    cut = 10;
}
else if (dist == 80) {
    cut = 10;
}
else if (dist == 90) {
    cut = 7;
}
else if (dist == 100){
    cut = 6;
}
else if (dist == 110){
    cut = 5;
}
else if (dist == 120){
    cut = 5;
}
else if (dist == 130){
    cut = 5;
}
else if (dist == 140){
    cut = 5;
}
else {
    G4cerr << "Invalid Distance!" << G4endl;
    exit(0);
}
}
#endif