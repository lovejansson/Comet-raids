#include <cmath>
#include <vector>
// this can be used to calculate damage of an object hitting the player or how much the player gets hurt by hitting the wall or the damage of a projectile... 

double calc_energy_kinetic(double const mass, double const velocity)
{
    /* mass is messured in kg and velosity in m/s */
    return mass * velocity; // Joule
}

double calc_impulse(double const force, double const period)
{
    /*
        important note this is average force that means we assume instant max force and instant
        shutof when using this to calculate acceleration
        further more an impulse is the change in movment ie mass1 * velocity1 - mass2 * velosity2
    */
    return force * period;
}

///////////////////
// Newtons laws //
///////////////////

// first law



// second law
/*
1 neuton == 1kg * 1m / 1s**2  == 1kg * 1a
a = 1 == 1m / 1s**2
*/

double calc_acceleration(double const force,double const mass)
{
    return force / mass;
}

double calc_force( double const mass, double const acceleration)
{
    return mass * acceleration;
}

// third law


// newtons law of gravitation
/* 
    r = distande between två objects
    m1 = mass of object 1
    m2 = mass of object 2
    G = Gravity konstant == 6,67 * 10^-11
*/

//Gravity constant is a constant global variable.
double const G{6.673 * pow(10, -11)};

double calc_gravitational_force(double const mass1, double const mass2, double const distance)
{
    double product_of_masses{mass1 * mass2};
    return G * product_of_masses / pow(distance, 2);
}


// kollisioner helt inelastiska. lämpligt för is. 
/* 
    hastighet på ett tvådimentionellt plan kan beskrivs som vektorer
    en vektor är förändringen i x och y let över en given tid (1 sekund)
    genom att bryta ned en rikting i en hastig het i x led (vektor x = 1 tex)
    och y led ( vektor y = 0 tex) så får vi en sammansatt hastighet v = (vektor_x,vektor_y) = (1,0)
    dvs detta föremål rör sig rakt å höger

    x > 0 == höger
    x < 0 == vänster
    y > 0 == uppåt
    y < 0 == nedåt 

    om två föremål colliderar så adderas deras vektorer ex

    add vectors(obj1, obj2)

    och ett nytt föremål skapas

    vektor som får via get_vector() bör vara viktad med föremålets vikt.
    dvs
    v1_true = (3, 0) 
    obj1 mass = 10
    v1_relative = 10* (3,0) = (30,0)

    efter collision så måste nya vektorn delas med nya vikten

    v2_true = (0,3)
    obj2_mass = 40
    v2_relative = 40 * (0,3) = (0, 120)
    
    new_obj mass = 50
    new obj v_relative = (30, 120)
    new obj v_true = (30, 120)/50 = (30/50 , 120/50) = (0.6, 2.4)

    normaliserad vektor(vektor/hypotinusan) * massa * hastighet(hypotenusan)

*/

add_vectors(obj obj1, obj onj2)
{
    v1 = obj1.get_vector();
    v2 = obj2.get_vector();

    double obj1_vector_x = v1[0];
    double obj1_vector_y = v1[1];

    double obj2_vector_x = v2[0];    
    double obj2_vector_y = v2[1];

    new_vector = (obj1_vector_x + obj2_vector_x, obj1_vector_y + obj2_vector_y);

    return new_vector;
} 


vector calc_new_speed()
{
    
}
