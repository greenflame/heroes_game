#include "unit.h"

Unit::Unit()
{

}

Unit::Unit(QString name, QString picture, QString faction, int level,
           char upgrade, int attack, int defence, int damage_from,
           int damage_to, Attack attack_type, int health, int speed,
           Movement movement_type, int size, int cost)
{
    this->name = name;
    this->picture = picture;
    this->faction = faction;
    this->level = level;
    this->upgrade = upgrade;
    this->attack = attack;
    this->defence = defence;
    this->damage_from = damage_from;
    this->damage_to = damage_to;
    this->attack_type = attack_type;
    this->health = health;
    this->speed = speed;
    this->movement_type = movement_type;
    this->size = size;
    this->cost = cost;
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

    // name, picture, faction, level, upgrade, attack, defence, damage_from, damage_to, attack_type, health, speed, movement_type, size, cost

    units.insert("Pikeman", Unit("Pikeman", "h6_unit_Haven_1a_Sentinel.png", "Castle", 1, 'a', 4, 5, 1, 3, MELEE, 10, 4, WALKING, 1, 60));
    units.insert("Halberdier", Unit("Halberdier", "h6_unit_Haven_1b_Praetorian.png", "Castle", 1, 'b', 6, 5, 2, 3, MELEE, 10, 5, WALKING, 1, 75));
    units.insert("Archer", Unit("Archer", "h6_unit_Haven_2a_Crossbowman.png", "Castle", 2, 'a', 6, 3, 2, 3, DISTANT, 10, 4, WALKING, 1, 100));
    units.insert("Marksman", Unit("Marksman", "h6_unit_Haven_2b_Marksman.png", "Castle", 2, 'b', 6, 3, 2, 3, DISTANT, 10, 6, WALKING, 1, 150));
    units.insert("Griffin", Unit("Griffin", "h6_unit_Haven_3a_Sister.png", "Castle", 3, 'a', 8, 8, 3, 6, MELEE, 25, 6, FLYING, 2, 200));
    units.insert("Royal Griffin", Unit("Royal Griffin", "h6_unit_Haven_3b_Vestal.png", "Castle", 3, 'b', 9, 9, 3, 6, MELEE, 25, 9, FLYING, 2, 240));
    units.insert("Swordsman", Unit("Swordsman", "h6_unit_Haven_4a_Griffin.png", "Castle", 4, 'a', 10, 12, 6, 9, MELEE, 35, 5, WALKING, 1, 300));
    units.insert("Crusader", Unit("Crusader", "h6_unit_Haven_4b_Imperial_Griffin.png", "Castle", 4, 'b', 12, 12, 7, 10, MELEE, 35, 6, WALKING, 1, 400));
    units.insert("Monk", Unit("Monk", "h6_unit_Haven_5a_Radiant_Glory.png", "Castle", 5, 'a', 12, 7, 10, 12, DISTANT, 30, 5, WALKING, 1, 400));
    units.insert("Zealot", Unit("Zealot", "h6_unit_Haven_5b_Blazing_Glory.png", "Castle", 5, 'b', 12, 10, 10, 12, DISTANT, 30, 7, WALKING, 1, 450));
    units.insert("Cavalier", Unit("Cavalier", "h6_unit_Haven_6a_Sun_Rider.png", "Castle", 6, 'a', 15, 15, 15, 25, MELEE, 100, 7, WALKING, 2, 1000));
    units.insert("Champion", Unit("Champion", "h6_unit_Haven_6b_Sun_Crusader.png", "Castle", 6, 'b', 16, 16, 20, 25, MELEE, 100, 9, WALKING, 2, 1200));
    units.insert("Angel", Unit("Angel", "h6_unit_Haven_7a_Seraph.png", "Castle", 7, 'a', 20, 20, 50, 50, MELEE, 200, 12, FLYING, 1, 3000));
    units.insert("Archangel", Unit("Archangel", "h6_unit_Haven_7b_Celestial.png", "Castle", 7, 'b', 30, 30, 50, 50, MELEE, 250, 18, FLYING, 2, 5000));

    units.insert("Imp", Unit("Imp", "h6_unit_Inferno_1a_Maniac.png", "Inferno", 1, 'a', 2, 3, 1, 2, MELEE, 4, 5, WALKING, 1, 50));
    units.insert("Familiar", Unit("Familiar", "h6_unit_Inferno_1b_Demented.png", "Inferno", 1, 'b', 4, 4, 1, 2, MELEE, 4, 7, WALKING, 1, 60));
    units.insert("Gog", Unit("Gog", "h6_unit_Inferno_2a_Hell_Hound.png", "Inferno", 2, 'a', 6, 4, 2, 4, DISTANT, 13, 4, WALKING, 1, 125));
    units.insert("Magog", Unit("Magog", "h6_unit_Inferno_2b_Cerberus.png", "Inferno", 2, 'b', 7, 4, 2, 4, DISTANT, 13, 6, WALKING, 1, 175));
    units.insert("Hound", Unit("Hound", "h6_unit_Inferno_3a_Succubus.png", "Inferno", 3, 'a', 10, 6, 2, 7, MELEE, 25, 7, WALKING, 2, 200));
    units.insert("Cerberus", Unit("Cerberus", "h6_unit_Inferno_3b_Lilim.png", "Inferno", 3, 'b', 10, 8, 2, 5, MELEE, 25, 8, WALKING, 2, 250));
    units.insert("Demon", Unit("Demon", "h6_unit_Inferno_4a_Breeder.png", "Inferno", 4, 'a', 10, 10, 7, 9, MELEE, 35, 5, WALKING, 1, 250));
    units.insert("Horned Demon", Unit("Horned Demon", "h6_unit_Inferno_4b_Breeder_Mother.png", "Inferno", 4, 'b', 10, 10, 7, 9, MELEE, 40, 6, WALKING, 1, 270));
    units.insert("Pit Fiend", Unit("Pit Fiend", "h6_unit_Inferno_5a_Tormentor.png", "Inferno", 5, 'a', 13, 13, 13, 17, MELEE, 45, 6, WALKING, 1, 500));
    units.insert("Pit Lord", Unit("Pit Lord", "h6_unit_Inferno_5b_Lacerator.png", "Inferno", 5, 'b', 13, 13, 13, 17, MELEE, 45, 7, WALKING, 1, 700));
    units.insert("Efreet", Unit("Efreet", "h6_unit_Inferno_6a_Juggernaut.png", "Inferno", 6, 'a', 16, 12, 16, 24, MELEE, 90, 9, FLYING, 1, 900));
    units.insert("Efreet Sultan", Unit("Efreet Sultan", "h6_unit_Inferno_6b_Ravager.png", "Inferno", 6, 'b', 16, 14, 16, 24, MELEE, 90, 13, FLYING, 1, 1100));
    units.insert("Devil", Unit("Devil", "h6_unit_Inferno_7a_Pit_Fiend.png", "Inferno", 7, 'a', 19, 21, 30, 40, MELEE, 160, 11, FLYING, 1, 2700));
    units.insert("Arch Devil", Unit("Arch Devil", "h6_unit_Inferno_7b_Pit_Lord.png", "Inferno", 7, 'b', 26, 28, 30, 40, MELEE, 200, 17, FLYING, 1, 4500));

    units.insert("Skeleton", Unit("Skeleton", "h6_unit_Necropolis_1a_Skeleton.png", "Necropolis", 1, 'a', 5, 4, 1, 3, MELEE, 6, 4, WALKING, 1, 60));
    units.insert("Skeleton Warrior", Unit("Skeleton Warrior", "h6_unit_Necropolis_1b_Skeletal_Spearman.png", "Necropolis", 1, 'b', 6, 6, 1, 3, MELEE, 6, 5, WALKING, 1, 70));
    units.insert("Walking Dead", Unit("Walking Dead", "h6_unit_Necropolis_2a_Ghoul.png", "Necropolis", 2, 'a', 5, 5, 2, 3, MELEE, 15, 3, WALKING, 1, 100));
    units.insert("Zombie", Unit("Zombie", "h6_unit_Necropolis_2b_Ravenous_Ghoul.png", "Necropolis", 2, 'b', 5, 5, 2, 3, MELEE, 20, 4, WALKING, 1, 125));
    units.insert("Wight", Unit("Wight", "h6_unit_Necropolis_3a_Ghost.png", "Necropolis", 3, 'a', 7, 7, 3, 5, MELEE, 18, 5, FLYING, 1, 200));
    units.insert("Wraith", Unit("Wraith", "h6_unit_Necropolis_3b_Specter.png", "Necropolis", 3, 'b', 7, 7, 3, 5, MELEE, 18, 7, FLYING, 1, 230));
    units.insert("Vampire", Unit("Vampire", "h6_unit_Necropolis_4a_Lich.png", "Necropolis", 4, 'a', 10, 9, 5, 8, MELEE, 30, 6, FLYING, 1, 360));
    units.insert("Vampire Lord", Unit("Vampire Lord", "h6_unit_Necropolis_4b_Archlich.png", "Necropolis", 4, 'b', 10, 10, 5, 8, MELEE, 40, 9, FLYING, 1, 500));
    units.insert("Lich", Unit("Lich", "h6_unit_Necropolis_5a_Lamasu.png", "Necropolis", 5, 'a', 13, 10, 11, 13, DISTANT, 30, 6, WALKING, 1, 550));
    units.insert("Power Lich", Unit("Power Lich", "h6_unit_Necropolis_5b_Putrid_Lamasu.png", "Necropolis", 5, 'b', 13, 10, 11, 15, DISTANT, 40, 7, WALKING, 1, 600));
    units.insert("Black Knight", Unit("Black Knight", "h6_unit_Necropolis_6a_Vampire.png", "Necropolis", 6, 'a', 16, 16, 15, 30, MELEE, 120, 7, WALKING, 2, 1200));
    units.insert("Dread Knight", Unit("Dread Knight", "h6_unit_Necropolis_6b_Vampire_Lord.png", "Necropolis", 6, 'b', 18, 18, 15, 30, MELEE, 120, 9, WALKING, 2, 1500));
    units.insert("Bone Dragon", Unit("Bone Dragon", "h6_unit_Necropolis_7a_Fate_Spinner.png", "Necropolis", 7, 'a', 17, 15, 25, 50, MELEE, 150, 9, FLYING, 2, 1800));
    units.insert("Ghost Dragon", Unit("Ghost Dragon", "h6_unit_Necropolis_7b_Fate_Weaver.png", "Necropolis", 7, 'b', 19, 17, 25, 50, MELEE, 200, 14, FLYING, 2, 3000));

    return units;
}
