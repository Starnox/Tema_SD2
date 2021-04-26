/* MIHAILEACU Eduard-Florin - 312CB */
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
                top10 = NULL, all = NULL, residuu = NULL;

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

            fprintf(outputFile,"Serialul %s a fost adaugat la pozitia %d.\n",
                     newSeries->name, position);
            
            // insert in the all list which contains all the series
            OrdererdInsert(&all, newSeries, CompareSeries, &position);

        }
        else if(strcmp(command, "show") == 0)
        {
            char category[DIM_MAX];
            fscanf(inputFile ,"%s", category);
            fprintf(outputFile, "Categoria %s: ", category);

            // check for the category and display the list
            if(strcmp(category, "1") == 0)
                DisplayList(tendinte, DisplaySeries, outputFile);

            else if(strcmp(category, "2") == 0)
                DisplayList(documentare, DisplaySeries, outputFile);    

            else if(strcmp(category, "3") == 0)
                DisplayList(tutoriale, DisplaySeries, outputFile);

            else if(strcmp(category, "top10") == 0)
                DisplayList(top10, DisplaySeries, outputFile);

            else if(strcmp(category, "later") == 0)
                DisplayQueue(&watch_later, DisplaySeries, outputFile);

            else if(strcmp(category, "watching") == 0)
                DisplayStack(&currently_watching, DisplaySeries, outputFile);

            else if(strcmp(category, "history") == 0)
                DisplayStack(&history, DisplaySeries, outputFile);

        }
        else if(strcmp(command, "add_sez") == 0)
        {
            char name[DIM_MAX];
            fscanf(inputFile,"%s",name);
            
            // search through all the lists for the series with the given name
            TSeriesPointer currSeries = (TSeriesPointer) FindElement(all, name, MyFindFunction);
            // if we find the series
            if(currSeries != NULL)
            {
                TSeasonPointer newSeason = ReadSeason(inputFile);
                AddSeason(currSeries, newSeason);
                fprintf(outputFile,"Serialul %s are un sezon nou.\n", currSeries->name);
            }
            else
            {
                printf("Serialul nu exista\n");
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

            // remove the nodes from all the other lists
            RemoveFromList(&tendinte, currSeries, FindFunctionForTwoNodes);
            RemoveFromList(&documentare, currSeries, FindFunctionForTwoNodes);
            RemoveFromList(&tutoriale, currSeries, FindFunctionForTwoNodes);

            RemoveFromList(&top10, currSeries, FindFunctionForTwoNodes);
            ReadjustOrder(top10); // decrement the order
        }
        
        else if(strcmp(command, "watch") == 0)
        {
            // read the input
            char name[DIM_MAX];
            int duration;

            fscanf(inputFile, "%s %d", name, &duration);
            // check if the series is in the stack
            TSeriesPointer searchStack = (TSeriesPointer) 
                                FindElementInStack(&currently_watching, name, MyFindFunction);

             // find the series in the all list
            TSeriesPointer currSeries = (TSeriesPointer) FindElement(all, name, MyFindFunction);

            if(currSeries == NULL) // couldn't find the series
            {
                printf("Serialul nu exista\n");
                continue;
            }
            // if the series is not in the stack
            if(searchStack == NULL)
            {
                // move the series to the stack
                PushStack(currently_watching, currSeries);

                // remove the series from the other lists
                // remove the nodes from all the other lists
                RemoveFromList(&tendinte, currSeries, FindFunctionForTwoNodes);
                RemoveFromList(&documentare, currSeries, FindFunctionForTwoNodes);
                RemoveFromList(&tutoriale, currSeries, FindFunctionForTwoNodes);
                RemoveFromQueueList(&watch_later, currSeries, FindFunctionForTwoNodes);


                RemoveFromList(&top10, currSeries, FindFunctionForTwoNodes);
                ReadjustOrder(top10); // decrement the order
            }
            else
            {
                // must bring the series to the top of the stack
                RemoveFromStackList(&currently_watching, searchStack, FindFunctionForTwoNodes);
                PushStack(currently_watching, searchStack);
            }

            // Watch x duration from the series
            int result = WatchSeries(currSeries, duration, outputFile);

            // we watched the whole series
            if(result == 1)
            {
                // eliminate the series from the stack
                PopStack(currently_watching);
                // and add it to the history stack
                PushStack(history, currSeries);
            }
            
        }
        else if(strcmp(command, "add_top") == 0)
        {
            int position;
            // this read will put the position in the id field
            TSeriesPointer newSeries = ReadSeries(inputFile);

            // modify the id and nrOrder fields with the correct information
            int aux = newSeries->id;
            newSeries->id = 4;
            newSeries->nrOrder = aux;

            if(aux > 10)
                continue;

            // add to the all list
            OrdererdInsert(&all, newSeries, CompareSeries, &position);

            // add to top 10 list
            OrdererdInsert(&top10, newSeries, CompareSeriesFromTop, &position);

            // Check if there are more than 10 series in the top
            TSeriesPointer toEliminate = VerifyIntegrity(top10);
            if(toEliminate != NULL)
                OrdererdInsert(&residuu, toEliminate, CompareSeries, &position);
            ReadjustOrder(top10);

            

            // Display the new top10 list
            fprintf(outputFile, "Categoria top10: ");
            DisplayList(top10, DisplaySeries, outputFile);
             
        }
    }

    free(command);
    DestroyList(&all, FreeSeries, 0);
    DestroyList(&tendinte, FreeSeries, 1);
    DestroyList(&documentare, FreeSeries, 1);
    DestroyList(&tutoriale, FreeSeries, 1);
    DestroyList(&top10, FreeSeries, 1);
    DestroyList(&residuu, FreeSeries, 1);
    ClearQueue(watch_later, FreeSeries);
    ClearStack(currently_watching, FreeSeries);
    ClearStack(history, FreeSeries);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

void ReadjustOrder(TNodePointer node)
{
    int correctIndex = 1;

    while(node != NULL)
    {
        TSeriesPointer seriesInfo = (TSeriesPointer) node->info;
        seriesInfo->nrOrder = correctIndex;

        correctIndex++;
        node = node->next;
    }
}

TSeriesPointer VerifyIntegrity(TNodePointer node)
{
    TNodePointer pre = NULL;
    int index = 0;
    while(node != NULL)
    {
        index++;
        if(index == 11)
        {
            TSeriesPointer info = node->info;
            // delete this node and free the info
            DestroyNode(&node, FreeSeries, 0);
            pre->next = NULL;
            return info;
        }
        pre = node;
        node = node->next;
    }
    return NULL;
}

int WatchSeries(TSeriesPointer series, int duration, FILE *outputFile)
{
    int aux;;

    // get the seasons queue
    TQueuePointer seasonQueue = series->seasons;

    // go through every season in the queue

    while(!IsEmptyQueue(seasonQueue))
    {
        // get the current season
        TSeasonPointer currSeason = (TSeasonPointer) QueueTop(seasonQueue);

        // get the episodes queue for the season
        TQueuePointer episodeQueue = currSeason->episodes;

        while(!IsEmptyQueue(episodeQueue))
        {
            // get the current episode
            TEpisodePointer currEpisode = (TEpisodePointer) QueueTop(episodeQueue);
            aux = currEpisode->duration;
            currEpisode->duration -= duration;

            if(currEpisode->duration <= 0)
            {
                // eliminate the episode from the queue
                void *info = QueuePop(episodeQueue);

                // free the episode
                free(info);
            }

            duration-= aux;
            if(duration <= 0)
            {
                break;
            }
        }

        // if we watched every episode from the season
        if(IsEmptyQueue(episodeQueue))
        {
            // eliminate the season from the queue
            void *info =QueuePop(seasonQueue);
            FreeSeason(info);
        }

        if(duration <= 0)
        {
            break;
        }
    }

    // if we watched the whole series
    if(IsEmptyQueue(seasonQueue))
    {
        // remove the series from the watching_stack
        fprintf(outputFile, "Serialul %s a fost vizionat integral.\n",series->name);
        return 1;
    }
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

int CompareSeriesFromTop(void *seriesA, void *seriesB)
{
    TSeriesPointer seriesA_info = (TSeriesPointer) seriesA;
    TSeriesPointer seriesB_info = (TSeriesPointer) seriesB;

    return seriesB_info->nrOrder - seriesA_info->nrOrder;
}

int CompareSeries(void * seriesA, void *seriesB)
{
    TSeriesPointer seriesA_info = (TSeriesPointer) seriesA;
    TSeriesPointer seriesB_info = (TSeriesPointer) seriesB;
    if(seriesA_info->rating == seriesB_info->rating)
    {
        return strcmp(seriesB_info->name, seriesA_info->name);
    }
    if(seriesA_info->rating < seriesB_info->rating)
        return -1;
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
