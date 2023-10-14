/*
 * Graduation internship application - Prodrive Technologies
 * Challenge: Music playlist (C)
 * Author: Alexandru-Răzvan Pășescu
 * Date: 1 November 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

int add_song_end(struct Playlist **list)
{
    // Allocate memory for new playlist node
    struct Playlist *newSong;
    newSong = (struct Playlist*)malloc(sizeof(struct Playlist));
    if (newSong == NULL)
    {
        printf ("Error: could not allocate memory for a new song!\n");
        return (-1);
    }

    // Populate song information fields
    _get_new_song_data(newSong);

    // Reach last node in list and store new song in the 'next' field
    if (*list == NULL)
    {
        *list = newSong;
    }
    else
    {
        struct Playlist *temp = *list;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newSong;
    }
    
    printf ("Song was added to the playlist!\n");
    update_playlist_datafile(*list);
    return (0);
}

int remove_song_end(struct Playlist **list)
{
    int nrSongs = _count_playlist_songs(*list);
    if (nrSongs == 0)
    {
        printf ("Playlist is empty!\n");
        return (-1);
    }
    else if (nrSongs == 1)
    {
        struct Playlist *temp = *list;
        printf ("Removed song: \"%s\" by %s\n", \
            temp->data.song, temp->data.artist);
        free(*list);
        *list = NULL;
    }
    else
    {
        // Reach second to last song in playlist and remove the last song
        struct Playlist *temp = *list;
        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }
        printf ("Removed song: \"%s\" by %s\n", \
            temp->next->data.song, temp->next->data.artist);
        free(temp->next);
        temp->next = NULL;
    }

    update_playlist_datafile(*list);
    return (0);
}

int add_song_middle(struct Playlist *list)
{
    // Allocate memory for new playlist node
    struct Playlist *newSong;
    newSong = (struct Playlist*)malloc(sizeof(struct Playlist));
    if (newSong == NULL)
    {
        printf ("Error: could not allocate memory for a new song!\n");
        return (-1);
    }

    int nrSongs = _count_playlist_songs(list);
    if (nrSongs < 2)
    {
        printf ("Error: could not complete operation!\n");
        printf ("Playlist must contain at least 2 songs for insertion to make sense\n");
        return (-1);
    }
    else
    {
        // Get place in playlist to insert new song
        int rank;
        printf ("There are %d songs in the playlist, current song is rank 1\n", \
            nrSongs);
        printf ("A new song can be inserted between rank 1 and rank %d\n", \
            nrSongs - 1);
        printf ("After which playlist rank should the song be inserted?: ");
        scanf("%d", &rank);

        if (rank >= 1 && rank < nrSongs)
        {
             _get_new_song_data(newSong);

             // Reach song just before the specified rank and insert new song after it
            struct Playlist *temp = list;
            for (int i = 1; i < rank; i++)
            {
                temp = temp->next;
            }
            newSong->next = temp->next;
            temp->next = newSong;
            printf ("Song was added to the playlist!\n");
        }
        else
        {
            printf ("Error: invalid rank!\n");
            return (-1);
        }
    }

    update_playlist_datafile(list);
    return (0);
}

void print_playlist(struct Playlist *list)
{
    if (list == NULL)
    {
        printf ("Playlist is empty!\n");
    }
    else
    {
        printf ("Playlist contents:\n");
        struct Playlist *temp = list;
        while (temp != NULL)
        {
            printf ("\"%s\" by %s\n", \
                temp->data.song, temp->data.artist);
            temp = temp->next;
        }
    }
}

int play_next_song(struct Playlist **list)
{
    int nrSongs = _count_playlist_songs(*list);
    if (nrSongs == 0)
    {
        printf ("Playlist is empty!\n");
        return (-1);
    }
    else if (nrSongs == 1)
    {
        printf ("End of playlist has been reached!\n");
        free(*list);
        *list = NULL;
    }
    else
    {
        // Move head of playlist to next song and free current song
        struct Playlist *temp = *list;
        printf ("Playing next song: \"%s\" by %s\n", \
            temp->next->data.song, temp->next->data.artist);
        *list = temp->next;
        free(temp);
    }
    
    update_playlist_datafile(*list);
    return (0);
}

int extract_playlist_datafile(struct Playlist **list)
{
    FILE *f;
    f = fopen("playlist_data.txt", "r");
	if (f != NULL)
	{
        printf ("Found existing playlist data file; extracting contents...\n");

        // Prevent empty file from counting as entry
        int size = 0;
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        rewind(f);

        while (!feof(f) && size > 0)
        {
            // Allocate memory for new playlist node
            struct Playlist *newSong;
            newSong = (struct Playlist*)malloc(sizeof(struct Playlist));
            if (newSong == NULL)
            {
                printf ("Error: could not allocate memory for a new song!\n");
                return (-1);
            }

            // Read and store playlist entries line by line, taking care
            // to remove the newline introduced by fgets()
            fgets(newSong->data.song, MAX_STRING_LEN, f);
            newSong->data.song[strlen(newSong->data.song)-1] = '\0';
            fgets(newSong->data.artist, MAX_STRING_LEN, f);
            newSong->data.artist[strlen(newSong->data.artist)-1] = '\0';
            newSong->next = NULL; // Point 'next' to NULL by default

            // Reach last node in list and store new song in the 'next' field
            if (*list == NULL)
            {
                *list = newSong;
            }
            else
            {
                struct Playlist *temp = *list;
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = newSong;
            }
        }
	}
    else
    {
        printf ("No existing playlist data was found; a new file will be created\n");
        f = fopen("playlist_data.txt", "w");
    }
    fclose(f);
    return (0);
}

void update_playlist_datafile(struct Playlist *list)
{
    FILE *f;
    f = fopen("playlist_data.txt", "w"); // Clears existing file
    if (list != NULL)
    {
        struct Playlist *temp = list;
        fputs(temp->data.song, f);
        fputs("\n", f);
        fputs(temp->data.artist, f);
        while (temp->next != NULL)
        {
            temp = temp->next;
            fputs("\n", f);
            fputs(temp->data.song, f);
            fputs("\n", f);
            fputs(temp->data.artist, f);
        }
    }
    fclose(f);
}

void _get_new_song_data(struct Playlist *newSong)
{
    printf ("Please specify the song name (max. 50 characters): ");
    getchar(); // Clear input buffer before fgets()
    fgets(newSong->data.song, MAX_STRING_LEN, stdin);

    printf ("Please specify the artist (max. 50 characters): ");
    //getchar();
    fgets(newSong->data.artist, MAX_STRING_LEN, stdin);

    // Remove newline character added by fgets() from input strings
    newSong->data.song[strlen(newSong->data.song) - 1] = '\0';
    newSong->data.artist[strlen(newSong->data.artist) - 1] = '\0';

    newSong->next = NULL; // Point 'next' to NULL by default
}

int _count_playlist_songs(struct Playlist *list)
{
    int count = 0;
    if (list != NULL)
    {
        count++;
        struct Playlist *temp = list;
        while (temp->next != NULL)
        {
            count++;
            temp = temp->next;
        }
    }
    return count;
}