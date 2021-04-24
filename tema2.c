#include "tema2.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Introdu numarul corect de parametri");
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");

    TNodePointer tendinte = NULL, documentare = NULL, tutoriale = NULL,
                top10 = NULL, all = NULL;

    // all -o lista cu toate serialele

    TQueuePointer watch_later = InitialiseQueue();
    TStackPointer currently_watching = InitialiseStack();
    TStackPointer history = InitialiseStack();


    char *command = (char *) malloc(sizeof(char) * DIM_MAX);

    int position;
    while(fscanf(inputFile, "%s", command) != EOF)
    {
        // check for the commands
        if(strcmp(command,"add") == 0)
        {
            position = 0;
            // read the season
            TSeriesPointer newSeries = ReadSeries(inputFile);

            // check for the id and insert accordingly
            if(newSeries->id == 1)
                OrdererdInsert(&tendinte, newSeries, CompareSeries, &position);

            else if(newSeries->id == 2)
                OrdererdInsert(&documentare, newSeries, CompareSeries, &position);

            else if(newSeries->id == 3)
                OrdererdInsert(&tutoriale, newSeries, CompareSeries, &position);

            fprintf(outputFile,"Serialul %s a fost adaugat la pozitia %d.\n", newSeries->name, position);
            OrdererdInsert(&all, newSeries, CompareSeries, &position);

        }
        else if(strcmp(command, "show") == 0)
        {
            char category[DIM_MAX];
            fscanf(inputFile ,"%s", category);
            fprintf(outputFile, "Categoria %s: ", category);
            if(strcmp(category, "1") == 0)
                DisplayList(tendinte, DisplaySeries, outputFile);

            else if(strcmp(category, "2") == 0)
                DisplayList(documentare, DisplaySeries, outputFile);    

            else if(strcmp(category, "3") == 0)
                DisplayList(tutoriale, DisplaySeries, outputFile);

            else if(strcmp(category, "top10") == 0)
                DisplayList(top10, DisplaySeries, outputFile);

            else if(strcmp(category, "later") == 0)
                DisplayQueue(watch_later, DisplaySeries, outputFile);

            else if(strcmp(category, "watching") == 0)
                DisplayStack(currently_watching, DisplaySeries, outputFile);

            else if(strcmp(category, "history") == 0)
                DisplayStack(history, DisplaySeries, outputFile);

        }
        else if(strcmp(command, "add_sez") == 0)
        {
            char name[DIM_MAX];
            fscanf(inputFile,"%s",name);
            
            // search through all the lists for the series with the given name
            TSeriesPointer currSeries = (TSeriesPointer) FindElement(all, name, MyFindFunction);
            if(currSeries != NULL)
            {
                TSeasonPointer newSeason = ReadSeason(inputFile);
                AddSeason(currSeries, newSeason);
                fprintf(outputFile,"Serialul %s are un sezon nou.\n", currSeries->name);
            }
        }
        else if(strcmp(command, "later") == 0)
        {
            char name[DIM_MAX];
            fscanf(inputFile, "%s", name);

            // search in all
            TSeriesPointer currSeries = (TSeriesPointer) FindElement(all, name, MyFindFunction);
            if(currSeries != NULL)
            {
                // push the information in to the queue
                QueuePush(watch_later, currSeries);
                fprintf(outputFile, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n",
                currSeries->name, watch_later->count);
            }

            // remove the nodes from all the other lits
            RemoveFromList(&tendinte, currSeries, FindFunctionForTwoNodes);
            RemoveFromList(&documentare, currSeries, FindFunctionForTwoNodes);
            RemoveFromList(&tutoriale, currSeries, FindFunctionForTwoNodes);

            // TODO decrement the other ranks in the top
            RemoveFromList(&top10, currSeries, FindFunctionForTwoNodes);
        }
        else if(strcmp(command, "watch") == 0)
        {
            printf("dsa");
        }
        else if(strcmp(command, "add_top") == 0)
        {
            printf("dsad");
        }
    }

    free(command);
    DestroyList(&all, FreeSeries, 1);
    DestroyList(&tendinte, FreeSeries, 0);
    DestroyList(&documentare, FreeSeries, 0);
    DestroyList(&tutoriale, FreeSeries, 0);
    DestroyList(&top10, FreeSeries, 0);
    ClearQueue(watch_later, FreeSeries);
    ClearStack(currently_watching, FreeSeries);
    ClearStack(history, FreeSeries);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

// a is the node info and b is the name
// return 1 if the node contains the given name, 0 otherwise
int MyFindFunction(void *a, void *b)
{
    TSeriesPointer aInfo = (TSeriesPointer) a;
    if(strcmp(aInfo->name, (char *) b) == 0)
    {
        return 1;
    }

    return 0;
}

int FindFunctionForTwoNodes(void *a, void *b)
{
    TSeriesPointer aInfo = (TSeriesPointer) a,
                    bInfo = (TSeriesPointer) b;

    if(strcmp(aInfo->name, bInfo->name) == 0)
    {
        return 1;
    }

    return 0;
}

int CompareSeries(void * seriesA, void *seriesB)
{
    TSeriesPointer seriesA_info = (TSeriesPointer) seriesA;
    TSeriesPointer seriesB_info = (TSeriesPointer) seriesB;
    if(seriesA_info->rating == seriesB_info->rating)
    {
        return strcmp(seriesB_info->name, seriesA_info->name);
    }
    if(seriesA_info->rating <= seriesB_info->rating)
    {
        return -1;
    }
    return 1;
}

TSeriesPointer ReadSeries(FILE *inputFile)
{
    int id;
    char name[DIM_MAX];
    double rating;
    int nrSeasons, nrEpisodes, duration;
    fscanf(inputFile,"%d %s %lf %d", &id, name, &rating, &nrSeasons);

    // create the series
    TSeriesPointer newSeries = InitialiseSeries(id, name, rating, nrSeasons);

    int i,j;
    // for each season
    for(i = 0; i < nrSeasons; ++i)
    {
        fscanf(inputFile,"%d", &nrEpisodes);

        // create a new season
        TSeasonPointer newSeason = InitialiseSeason(nrEpisodes);

        // for each episode
        for(j = 0; j < nrEpisodes; ++j)
        {
            fscanf(inputFile,"%d", &duration);

            // create a new episode
            TEpisodePointer newEpisode = InitialiseEpisode(duration);
            AddEpisode(newSeason, newEpisode); // add the episode to the current season
        }

        // add the season to the series
        AddSeason(newSeries, newSeason);
    }
    return newSeries;
}

TSeasonPointer ReadSeason(FILE *inputFile)
{
    int nrEpisodes, i, duration;

    fscanf(inputFile,"%d", &nrEpisodes);

    TSeasonPointer newSeason = InitialiseSeason(nrEpisodes);
    
    for(i = 0; i< nrEpisodes; ++i)
    {
        fscanf(inputFile,"%d", &duration);
        TEpisodePointer newEpisode = InitialiseEpisode(duration);

        AddEpisode(newSeason, newEpisode);
    }

    return newSeason;
}
