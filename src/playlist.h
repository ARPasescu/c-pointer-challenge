/*
 * Graduation internship application - Prodrive Technologies
 * Challenge: Music playlist (C)
 * Author: Alexandru-Răzvan Pășescu
 * Date: 1 November 2022
 */

#ifndef _PLAYLIST_H
#define _PLAYLIST_H

#define MAX_STRING_LEN 50 // Max string length for song and artist names

// Struct holding song information
struct Song
{
	char artist[MAX_STRING_LEN];
	char song[MAX_STRING_LEN];
};

// Linked list node that forms the playlist
struct Playlist
{
    struct Song data;
    struct Playlist *next;
};

// Playlist operations
// ---------------------------------------------------------------------

/// @brief Appends a song to the end of the playlist, moving the tail of
/// the linked list. Requests the song information from the user.
/// @param list Double pointer to the head of the playlist linked list.
/// @return 0 if the operation was successful, -1 otherwise.
int add_song_end(struct Playlist **list);

/// @brief Removes a song from the end of the playlist, moving the tail
/// of the linked list.
/// @param list Double pointer to the head of the playlist linked list.
/// @return 0 if the operation was successful, -1 otherwise.
int remove_song_end(struct Playlist **list);

/// @brief Inserts a song to the middle of the playlist at the specified
/// index, changing the links between the list nodes. Requests the song
/// information and the spot in the playlist to insert the song from the
/// user.
/// @param list Pointer to the head of the playlist linked list.
/// @return 0 if the operation was successful, -1 otherwise.
int add_song_middle(struct Playlist *list);

/// @brief Lists the contents of the playlist in order.
/// @param list Pointer to the head of the playlist linked list.
void print_playlist(struct Playlist *list);

/// @brief Increments the head of the playlist linked list, removing the
/// first song.
/// @param list Double pointer to the head of the playlist linked list.
/// @return 0 if the operation was successful, -1 otherwise.
int play_next_song(struct Playlist **list);

/// @brief Opens and extracts the contents of the playlist data file
/// into the playlist linked list.
/// @param list Double pointer to the head of the playlist linked list.
/// @return 0 if the operation was successful, -1 otherwise.
int extract_playlist_datafile(struct Playlist **list);

/// @brief Refreshes the contents of the playlist data file to reflect
/// the current state of the playlist linked list.
/// @param list Pointer to the head of the playlist linked list.
void update_playlist_datafile(struct Playlist *list);

// Helper functions
// ---------------------------------------------------------------------

/// @brief Retrieves song details from user input and forms song node for
/// linked list.
/// @param newSong Pointer to the node that will store the new song data
void _get_new_song_data(struct Playlist *newSong);

/// @brief Counts the number of songs in the playlist.
/// @param list Pointer to the head of the playlist linked list.
/// @return The number of songs in the playlist as an integer.
int _count_playlist_songs(struct Playlist *list);

#endif