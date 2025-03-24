#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_CITIES 7
#define NUM_NEURONS (NUM_CITIES * 2)
#define MAX_ITERATIONS 10000
#define INITIAL_LEARNING_RATE 0.8
#define INITIAL_RADIUS (NUM_NEURONS / 3) 
//adjacent matrixfor the given TSP graph
int tsp_graph[NUM_CITIES]
[NUM_CITIES] = {
    {0, 0, 10, 0, 0, 0, 12}, //city 1
{0, 0, 8, 12, 0, 0, 0}, // city 2
{10, 8, 0, 11, 9, 0, 0}, //city 3
{0, 12, 11, 0, 10, 0, 0}, // city 4
{0, 0, 9, 10, 0, 6, 7}, // city 5
{0 ,0, 0, 0, 6, 0, 9}, // city 6
{12, 0, 0, 0, 7, 9, 0}, // city 7
};
// Neuron structure
typedef struct {
    double x, y;
} Neuron;
Neuron neurons[NUM_NEURONS];
double learning_rate = 
INITIAL_LEARNING_RATE;
double radius = INITIAL_RADIUS;
// Function to calculate Euclidean distance
double euclidean_distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 -y2));
}
// Function to get a Gaussian neighborhood function
double neighborhood_function(int distance,double radius) {
    return exp(-((double) (distance *distance)) / (2 * radius * radius));
}
// Initialize neurons in a circular pattern
void initialize_neurons() {
    for (int i = 0; i < NUM_NEURONS; i++) {
        double angle = (2,0 * M_PI *i) / NUM_NEURONS;
    neurons[i].x = cos(angle);
neurons[i].y = sin(angle);}
}
// Train SOM for TSP
void train_SOM() {
    srand(time(NULL));
    for (int iter = 0; iter < MAX_ITERATIONS; iter++) {
        // Select a random city
        int city_idx = rand() % NUM_CITIES;
        double city_x = (double) (city_idx + 1) / NUM_CITIES;
        double city_y = (double) (rand() % 100) / 100.0;
        // Find the closest neuron (winner)
        int winner_idx = 0;
        double min_dist = euclidean_distance(neurons[0].x, neurons[0].y, city_x, city_y);
        for (int i = 1; i < NUM_NEURONS; i++) {
            double dist = euclidean_distance(neurons[i].x, neurons[i].y, city_x, city_y);
            if (dist < min_dist) {
                min_dist = dist;
                winner_idx = i;
            }
        }
        // Update neurons
        for (int i = 0; i < NUM_NEURONS; i++) {
            int dist_to_winner = abs(i - winner_idx);
            if (dist_to_winner > NUM_NEURONS / 2)
            dist_to_winner = NUM_NEURONS - dist_to_winner;
        double influence = neighborhood_function(dist_to_winner, radius);
        neurons[i].x += influence * learning_rate * (city_x -neurons[i].x);
        neurons[i].y += influence *learning_rate * (city_y - neurons[i].y);
        } 
        // Decay learning rate and radius
        learning_rate *= 0.9995;
        radius *= 0.9995;
    }
}
// Find the final TSP route based on neuron positions
void find_tsp_route() {
    printf("Final route order: \n");
    for (int i = 0; i < NUM_CITIES; i++) {
        printf("City %d -> ", i + 1); 
    }
    printf("City 1 (start)\n");
}
int main() {
    initialize_neurons();
    train_SOM();
    find_tsp_route();
    return 0;
} 