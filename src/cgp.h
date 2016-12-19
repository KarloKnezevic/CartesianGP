//
// Created by karlo on 13.12.2016..
//

#ifndef CGP_CGP_H
#define CGP_CGP_H

struct matrix;

/**
 * General evolutionary parameters.
 */
struct parameters;

/**
 * CGP chromosome instances.
 */
struct chromosome;

/**
 * Data used by fitness when calculating chromosome fitness.
 */
struct dataSet;

/**
 * Best chromosome found on each run.
 */
struct results;

//-----------------------------------------------------------------

struct parameters *initialiseParameters(
        const int numInputs,
        const int numNodes,
        const int numOutputs,
        const int arity
);

void freeParameters(struct parameters *params);

void printParameters(struct parameters *params);

//-----------------------------------------------------------------

/**
 * If one function name is given that function is added to the function set.
 * If multiple node function names are given then each must be separated by a ','.
 * @param params
 * @param functionNames
 */
void addNodeFunction(struct parameters *params, char const *functionNames);

/**
 * Adds custom node function to the set of functions.
 * @param params
 * @param function
 * @param functionName
 * @param maxNumInputs
 */
void addCustomNodeFunction(
        struct parameters *params,
        double (*function)(
                const int numInputs,
                const double *inputs,
				const double *weights
        ),
        char const *functionName,
        int maxNumInputs
);

void clearFunctionSet(struct parameters *params);

//-----------------------------------------------------------------

void setNumInputs(struct parameters *params, int numInputs);

void setNumNodes(struct parameters *params, int numNodes);

void setNumOutputs(struct parameters *params, int numOutputs);

void setArity(struct parameters *params, int arity);

//-----------------------------------------------------------------

void setMu(struct parameters *params, int mu);

void setLambda(struct parameters *params, int lambda);

/**
 * Evolutionary strategies other than '+' and ',' are invalid.
 * @param params
 * @param evolutionaryStrategy
 */
void setEvolutionaryStrategy(
        struct parameters *params,
        char evolutionaryStrategy
);

void setMutationRate(struct parameters *params, double mutationRate);

//-----------------------------------------------------------------

/**
 * The recurrent connection probability specifies the probability that
 * a mutation to a connection gene will create a recurrent connection.
 * @param params
 * @param recurrentConnectionProbability
 */
void setRecurrentConnectionProbability(
        struct parameters *params,
        double recurrentConnectionProbability
);

/**
 * Shortcut Connections specifies whether an output can
 * connect directly to an input.
 * 0 or 1 is valid.
 * @param params
 * @param shortcutConnections
 */
void setShortcutConnections(struct parameters *params, int shortcutConnections);

void setConnectionWeightRange(struct parameters *params, double weightRange);

//-----------------------------------------------------------------

/**
 * Fitness function returns error.
 * @param params
 * @param fitnessFunction
 * @param fitnessFunctionName
 */
void setCustomFitnessFunction(
        struct parameters *params,
        double (*fitnessFunction)(
                struct parameters *params,
                struct chromosome *chromo,
                struct dataSet *data
        ),
        char const *fitnessFunctionName
);

//-----------------------------------------------------------------

void setCustomSelectionScheme(
        struct parameters *params,
        void (*selectionScheme)(
                struct parameters *params,
                struct chromosome **parents,
                struct chromosome **candidateChromos,
                int numParents,
                int numCandidateChromos
        ),
        char const *selectionSchemeName
);

void setCustomReproductionScheme(
        struct parameters *params,
        void (*reproductionScheme)(
                struct parameters *params,
                struct chromosome **parents,
                struct chromosome **children,
                int numParents,
                int numCandidateChromos
        ),
        char const *reproductionSchemeName
);

//-----------------------------------------------------------------

/**
 * In all cases lower fitness values are used to represent fitter chromosome.
 * @param params
 * @param targetFitness
 */
void setTargetFitness(struct parameters *params, double targetFitness);

//-----------------------------------------------------------------

/**
 * Set predefine mutation type.
 * @param params
 * @param mutationType
 */
void setMutationType(struct parameters *params, const char *mutationType);

//-----------------------------------------------------------------

/**
 * Represents the number of generations which elapse between showing
 * the user the current best fitness.
 * @param params
 * @param updateFrequency
 */
void setUpdateFrequency(struct parameters *params, int updateFrequency);

//-----------------------------------------------------------------

struct chromosome *initialiseChromosome(struct parameters *params);

/**
 * Custom functions cannot be loaded.
 * @param file
 * @return
 */
struct chromosome *initialiseChromosomeFromFile(const char *file);

struct chromosome *initialiseChromosomeFromChromosome(
        struct chromosome *chromo
);

void freeChromosome(struct chromosome *chromo);

//-----------------------------------------------------------------

/**
 * Displays chromosome in human readable format.
 * Active nodes labeled with an '*'.
 * @param chromo
 */
void printChromosome(struct chromosome *chromo, int weights);

//-----------------------------------------------------------------

void executeChromosome(struct chromosome *chromo, struct matrix **inputs);

//-----------------------------------------------------------------

/**
 * Output is the index of the output to be retrieved.
 * @param chromo
 * @param output
 * @return
 */
struct matrix *getChromosomeOutput(struct chromosome *chromo, int output);

/**
 * Node is the index ot the node to be retrieved.
 * @param chromo
 * @param node
 * @return
 */
struct matrix *getChromosomeNodeValue(struct chromosome *chromo, int node);

/**
 * Returns 1 or 0 as active or inactive.
 * @param chromo
 * @param node
 * @return
 */
int isNodeActive(struct chromosome *chromo, int node);

//-----------------------------------------------------------------

void saveChromosome(struct chromosome *chromo, char const *fileName);

//-----------------------------------------------------------------

/**
 * Returns 0 or 1 if different or same.
 * @param chromoA
 * @param chromoB
 * @return
 */
int compareChromosomes(struct chromosome *chromoA, struct chromosome *chromoB);

//-----------------------------------------------------------------

void mutateChromosome(struct parameters *params, struct chromosome *chromo);

//-----------------------------------------------------------------

void removeInactiveNodes(struct chromosome *chromo);

//-----------------------------------------------------------------

/**
 * Set the fitness of the chromosome using the fitness function.
 * @param params
 * @param chromo
 * @param data
 */
void setChromosomeFitness(
        struct parameters *params,
        struct chromosome *chromo,
        struct dataSet *data
);

/**
 * resets all of the chromosome nodes to output zero.
 * @param chromo
 */
void resetChromosome(struct chromosome *chromo);

//-----------------------------------------------------------------

void copyChromosome(
        struct chromosome *chromoDest,
        struct chromosome *chromoSrc
);

//-----------------------------------------------------------------

int getNumChromosomeInputs(struct chromosome *chromo);

int getNumChromosomeNodes(struct chromosome *chromo);

int getNumChromosomeActiveNodes(struct chromosome *chromo);

int getNumChromosomeOutputs(struct chromosome *chromo);

int getChromosomeNodeArity(struct chromosome *chromo, int index);

double getChromosomeFitness(struct chromosome *chromo);

int getNumChromosomeActiveConnections(struct chromosome *chromo);

/**
 * If chromosome not trained, -1 returned.
 * @param chromo
 * @return
 */
int getChromosomeGenerations(struct chromosome *chromo);

//-----------------------------------------------------------------

struct dataSet *initialiseDataSetFromArrays(
        int numInputs,
        int numOutputs,
        int numSamples,
        double *inputs,
        double *outputs
);

/**
 * First line: in, out, #samples
 * > 2,3,4
 * > 1,2,3,4,5
 * > 6,7,8,9,10
 * > 11,12,13,14,15
 * > 16,17,18,19,20
 * @param file
 * @return
 */
struct dataSet *initialiseDataSetFromFile(char const *file);

void freeDataSet(struct dataSet *data);

void printDataSet(struct dataSet *data);

void saveDataSet(struct dataSet *data, char const *fileName);

int getNumDataSetInputs(struct dataSet *data);

int getNumDataSetOutputs(struct dataSet *data);

int getNumDataSetSamples(struct dataSet *data);

/**
 * Returns pointer to given index.
 * @param data
 * @param sample
 * @return
 */
struct matrix **getDataSetSampleInputs(struct dataSet *data, int sample);

/**
 * Returns input value for given sample index and input index.
 * @param data
 * @param sample
 * @param input
 * @return
 */
struct matrix *getDataSetSampleInput(struct dataSet *data, int sample, int input);

double *getDataSetSampleOutputs(struct dataSet *data, int sample);

double getDataSetSampleOutput(struct dataSet *data, int sample, int output);

//-----------------------------------------------------------------

void freeResults(struct results *rels);

void saveResults(struct results *rels, char const *fileName);

/**
 * Copy of the best chromosome found on the given run.
 * @param rels
 * @param run
 * @return
 */
struct chromosome* getChromosome(struct results *rels, int run);

int getNumChromosomes(struct results *rels);

/**
 * Avg fitness of the best chromosome.
 * @param rels
 * @return
 */
double getAverageFitness(struct results *rels);

/**
 * Median fitness of the best chromosome.
 * @param rels
 * @return
 */
double getMedianFitness(struct results *rels);

/**
 * Average active nodes of the best chromosome for each run in results.
 * @param rels
 * @return
 */
double getAverageActiveNodes(struct results *rels);

//-----------------------------------------------------------------

/**
 * Returns the best chromosome after applying CGP to given task.
 * @param params
 * @param data
 * @param numGens
 * @return
 */
struct chromosome* runCGP(
        struct parameters *params,
        struct dataSet *data,
        int numGens
);

/**
 * Returns result structure for each run.
 * @param params
 * @param data
 * @param numGens
 * @param numRuns
 * @return
 */
struct results* repeatCGP(
        struct parameters *params,
        struct dataSet *data,
        int numGens,
        int numRuns
);

void setRandomNumberSeed(unsigned int seed);

#endif //CGP_CGP_H
