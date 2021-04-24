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
        if(strcmp(command, "show") == 0)
        {
            int index;
            fscanf(inputFile ,"%d", &index);
            fprintf(outputFile, "Categoria %d: ", index);
            if(index == 1)
                DisplayList(tendinte, DisplaySeries, outputFile);
            else if(index == 2)
                DisplayList(documentare, DisplaySeries, outputFile);    
            else if(index == 3)
                DisplayList(tutoriale, DisplaySeries, outputFile);
            else if(index == 4)
                DisplayList(top10, DisplaySeries, outputFile);
        }
        if(strcmp(command, "add_sez") == 0)
        {
            char name[DIM_MAX];
            fscanf(inputFile,"%s",name);
            
            // search through all the lists for the series with the given name
            TSeriesPointer currSeries = FindElement(tendinte, name, MyFindFunction);
            if(currSeries != NULL)
            {
                printf("dsa");
            }
            // tendinte
            
        }
    }


    /*    
    TSeriesPointer test_series = InitialiseSeries(1,"ducu",8.9,3);
    TSeriesPointer test_series2 = InitialiseSeries(2,"ducu2", 9,2);

    QueuePush(watch_later, test_series);
    QueuePush(watch_later, test_series2);

    while(!IsEmptyQueue(watch_later))
    {
        void *info = QueuePop(watch_later);
        printf("%lf\n", ((TSeriesPointer)info)->rating);
        FreeSeries(info);
    }

    PushStack(currently_watching, test_series);
    PushStack(currently_watching, test_series2);

    while(!IsEmptyStack(currently_watching))
    {
        void *info = PopStack(currently_watching);
        printf("%lf\n", ((TSeriesPointer)info)->rating);
        FreeSeries(info);
    }
    */

    

    free(command);
    ClearQueue(watch_later, FreeSeries);
    ClearStack(currently_watching, FreeSeries);
    ClearStack(history, FreeSeries);
    DestroyList(&all, FreeSeries, 1);
    DestroyList(&tendinte, FreeSeries, 0);
    DestroyList(&documentare, FreeSeries, 0);
    DestroyList(&tutoriale, FreeSeries, 0);
    DestroyList(&top10, FreeSeries, 0);
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
