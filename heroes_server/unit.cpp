#include "unit.h"

Unit::Unit()
{

}

bool Unit::operator ==(const Unit &other) const
{
    return name == other.name &&
        picture == other.picture &&
        faction == other.faction &&
        level == other.level &&
        upgrade == other.upgrade &&
        attack == other.attack &&
        defence == other.defence &&
        damage_from == other.damage_from &&
        damage_to == other.damage_to &&
        attack_type == other.attack_type &&
        health == other.health &&
        speed == other.speed &&
        movement_type == other.movement_type &&
        size == other.size &&
        cost == other.cost;
}

QMap<QString, Unit> Unit::all()
{
    QMap<QString, Unit> units;

    Unit pikeman;
    pikeman.name = "Pikeman";
    pikeman.picture = "h6_unit_Haven_1a_Sentinel.png";
    pikeman.faction = "Castle";
    pikeman.level = 1;
    pikeman.upgrade = 'a';
    pikeman.attack = 4;
    pikeman.defence = 5;
    pikeman.damage_from = 1;
    pikeman.damage_to = 3;
    pikeman.attack_type = MELEE;
    pikeman.health = 10;
    pikeman.speed = 4;
    pikeman.movement_type = WALKING;
    pikeman.size = 1;
    pikeman.cost = 60;
    units.insert("Pikeman", pikeman);

    Unit halberdier;
    halberdier.name = "Halberdier";
    halberdier.picture = "h6_unit_Haven_1b_Praetorian.png";
    halberdier.faction = "Castle";
    halberdier.level = 1;
    halberdier.upgrade = 'b';
    halberdier.attack = 6;
    halberdier.defence = 5;
    halberdier.damage_from = 2;
    halberdier.damage_to = 3;
    halberdier.attack_type = MELEE;
    halberdier.health = 10;
    halberdier.speed = 5;
    halberdier.movement_type = WALKING;
    halberdier.size = 1;
    halberdier.cost = 75;
    units.insert("Halberdier", halberdier);

    Unit archer;
    archer.name = "Archer";
    archer.picture = "h6_unit_Haven_2a_Crossbowman.png";
    archer.faction = "Castle";
    archer.level = 2;
    archer.upgrade = 'a';
    archer.attack = 6;
    archer.defence = 3;
    archer.damage_from = 2;
    archer.damage_to = 3;
    archer.attack_type = DISTANT;
    archer.health = 10;
    archer.speed = 4;
    archer.movement_type = WALKING;
    archer.size = 1;
    archer.cost = 100;
    units.insert("Archer", archer);

    Unit marksman;
    marksman.name = "Marksman";
    marksman.picture = "h6_unit_Haven_2b_Marksman.png";
    marksman.faction = "Castle";
    marksman.level = 2;
    marksman.upgrade = 'b';
    marksman.attack = 6;
    marksman.defence = 3;
    marksman.damage_from = 2;
    marksman.damage_to = 3;
    marksman.attack_type = DISTANT;
    marksman.health = 10;
    marksman.speed = 6;
    marksman.movement_type = WALKING;
    marksman.size = 1;
    marksman.cost = 150;
    units.insert("Marksman", marksman);

    Unit griffin;
    griffin.name = "Griffin";
    griffin.picture = "h6_unit_Haven_3a_Sister.png";
    griffin.faction = "Castle";
    griffin.level = 3;
    griffin.upgrade = 'a';
    griffin.attack = 8;
    griffin.defence = 8;
    griffin.damage_from = 3;
    griffin.damage_to = 6;
    griffin.attack_type = MELEE;
    griffin.health = 25;
    griffin.speed = 6;
    griffin.movement_type = FLYING;
    griffin.size = 2;
    griffin.cost = 200;
    units.insert("Griffin", griffin);

    Unit royal_griffin;
    royal_griffin.name = "Royal Griffin";
    royal_griffin.picture = "h6_unit_Haven_3b_Vestal.png";
    royal_griffin.faction = "Castle";
    royal_griffin.level = 3;
    royal_griffin.upgrade = 'b';
    royal_griffin.attack = 9;
    royal_griffin.defence = 9;
    royal_griffin.damage_from = 3;
    royal_griffin.damage_to = 6;
    royal_griffin.attack_type = MELEE;
    royal_griffin.health = 25;
    royal_griffin.speed = 9;
    royal_griffin.movement_type = FLYING;
    royal_griffin.size = 2;
    royal_griffin.cost = 240;
    units.insert("royal griffin", royal_griffin);

    Unit swordsman;
    swordsman.name = "Swordsman";
    swordsman.picture = "h6_unit_Haven_4a_Griffin.png";
    swordsman.faction = "Castle";
    swordsman.level = 4;
    swordsman.upgrade = 'a';
    swordsman.attack = 10;
    swordsman.defence = 12;
    swordsman.damage_from = 6;
    swordsman.damage_to = 9;
    swordsman.attack_type = MELEE;
    swordsman.health = 35;
    swordsman.speed = 5;
    swordsman.movement_type = WALKING;
    swordsman.size = 1;
    swordsman.cost = 300;
    units.insert("Swordsman", swordsman);

    Unit crusader;
    crusader.name = "Crusader";
    crusader.picture = "h6_unit_Haven_4b_Imperial_Griffin.png";
    crusader.faction = "Castle";
    crusader.level = 4;
    crusader.upgrade = 'b';
    crusader.attack = 12;
    crusader.defence = 12;
    crusader.damage_from = 7;
    crusader.damage_to = 10;
    crusader.attack_type = MELEE;
    crusader.health = 35;
    crusader.speed = 6;
    crusader.movement_type = WALKING;
    crusader.size = 1;
    crusader.cost = 400;
    units.insert("Crusader", crusader);

    Unit monk;
    monk.name = "Monk";
    monk.picture = "h6_unit_Haven_5a_Radiant_Glory.png";
    monk.faction = "Castle";
    monk.level = 5;
    monk.upgrade = 'a';
    monk.attack = 12;
    monk.defence = 7;
    monk.damage_from = 10;
    monk.damage_to = 12;
    monk.attack_type = DISTANT;
    monk.health = 30;
    monk.speed = 5;
    monk.movement_type = WALKING;
    monk.size = 1;
    monk.cost = 400;
    units.insert("Monk", monk);

    Unit zealot;
    zealot.name = "Zealot";
    zealot.picture = "h6_unit_Haven_5b_Blazing_Glory.png";
    zealot.faction = "Castle";
    zealot.level = 5;
    zealot.upgrade = 'b';
    zealot.attack = 12;
    zealot.defence = 10;
    zealot.damage_from = 10;
    zealot.damage_to = 12;
    zealot.attack_type = DISTANT;
    zealot.health = 30;
    zealot.speed = 7;
    zealot.movement_type = WALKING;
    zealot.size = 1;
    zealot.cost = 450;
    units.insert("Zealot", zealot);

    Unit cavalier;
    cavalier.name = "Cavalier";
    cavalier.picture = "h6_unit_Haven_6a_Sun_Rider.png";
    cavalier.faction = "Castle";
    cavalier.level = 6;
    cavalier.upgrade = 'a';
    cavalier.attack = 15;
    cavalier.defence = 15;
    cavalier.damage_from = 15;
    cavalier.damage_to = 25;
    cavalier.attack_type = MELEE;
    cavalier.health = 100;
    cavalier.speed = 7;
    cavalier.movement_type = WALKING;
    cavalier.size = 2;
    cavalier.cost = 1000;
    units.insert("Cavalier", cavalier);

    Unit champion;
    champion.name = "Champion";
    champion.picture = "h6_unit_Haven_6b_Sun_Crusader.png";
    champion.faction = "Castle";
    champion.level = 6;
    champion.upgrade = 'b';
    champion.attack = 16;
    champion.defence = 16;
    champion.damage_from = 20;
    champion.damage_to = 25;
    champion.attack_type = MELEE;
    champion.health = 100;
    champion.speed = 9;
    champion.movement_type = WALKING;
    champion.size = 2;
    champion.cost = 1200;
    units.insert("Champion", champion);

    Unit angel;
    angel.name = "Angel";
    angel.picture = "h6_unit_Haven_7a_Seraph.png";
    angel.faction = "Castle";
    angel.level = 7;
    angel.upgrade = 'a';
    angel.attack = 20;
    angel.defence = 20;
    angel.damage_from = 50;
    angel.damage_to = 50;
    angel.attack_type = MELEE;
    angel.health = 200;
    angel.speed = 12;
    angel.movement_type = FLYING;
    angel.size = 1;
    angel.cost = 3000;
    units.insert("Angel", angel);

    Unit archangel;
    archangel.name = "Archangel";
    archangel.picture = "h6_unit_Haven_7b_Celestial.png";
    archangel.faction = "Castle";
    archangel.level = 7;
    archangel.upgrade = 'b';
    archangel.attack = 30;
    archangel.defence = 30;
    archangel.damage_from = 50;
    archangel.damage_to = 50;
    archangel.attack_type = MELEE;
    archangel.health = 250;
    archangel.speed = 18;
    archangel.movement_type = FLYING;
    archangel.size = 2;
    archangel.cost = 5000;
    units.insert("Archangel", archangel);

    return units;
}
