//
// Created by b.karjoo on 4/7/2017.
//

#ifndef BRIMUS_POSITION_H
#define BRIMUS_POSITION_H


class position {
    int _position = 0;
public:
    position() {}
    position(int qty) : _position(qty) {}
    int get_position() const;
    void add_to_position(int qty) { _position += qty; }
    position operator+(const position& other) const {
       return position(_position + other.get_position());
    }
    position operator-(const position& other) const {
        return position(_position - other.get_position());
    }
    position operator+(int qty) const {
        return position(_position + qty);
    }
    position operator-(int qty) const {
        return position(_position - qty);
    }
    void operator+=(int qty) {
        _position += qty;
    }
    void operator-=(int qty) {
        _position -= qty;
    }

};


#endif //BRIMUS_POSITION_H
