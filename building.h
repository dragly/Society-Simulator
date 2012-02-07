#ifndef BUILDING_H
#define BUILDING_H

class Building
{
public:
    Building();

    int x() { return _x; }
    int y() { return _y; }

    enum BuildingType {
        Store,
        Home,
        WorkPlace
    };
    BuildingType buildingType()  { return  _buildingType; }

private:
    int _x,_y;
    BuildingType _buildingType;

};

#endif // BUILDING_H
