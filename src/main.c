/*
 * Graduation internship application - Prodrive Technologies
 * Challenge: Music playlist (C)
 * Author: Alexandru-Răzvan Pășescu
 * Date: 1 November 2022
 * 
 * Solution features the implementation of the music playlist linked list
 * manipulation methods stored as a separate API library, and includes
 * extras such as an options menu for easy interfacing and persistent
 * data storage for the playlist contents.
 */

#include <stdio.h>
#include "playlist.h"

int main()
{
	printf ("Prodrive Technologies challenge: Music playlist (C)\n");

	struct Playlist *head = NULL; // Head of playlist linked list

	// If an initial playlist exists, open it and extract the data into
	// the linked list
	extract_playlist_datafile(&head);

	// Display options menu
	int choice = -1;
	while (choice != 0)
	{
		printf ("\nMusic playlist options menu\n");
		printf ("---------------------------\n");
		printf ("1: Add a song to the end of the playlist\n");
		printf ("2: Remove a song from the end of the playlist\n");
		printf ("3: Add a song in the middle of the playlist\n");
		printf ("4: Show playlist contents\n");
		printf ("5: Play the next song in the playlist\n");
		printf ("0: Quit\n");
		printf ("> ");
		scanf ("%d", &choice);

		// Execute the selected task
        switch (choice)
        {
            case 1: // Add a song to the end of the playlist
				add_song_end(&head);
                break;
            
            case 2: // Remove a song from the end of the playlist
				remove_song_end(&head);
                break;
            
            case 3: // Add a song in the middle of the playlist
				add_song_middle(head);
                break;
            
            case 4: // Show playlist contents
				print_playlist(head);
                break;
            
            case 5: // Play the next song in the playlist
				play_next_song(&head);
                break;
            
            case 0: // Quit
                break;
            
            default: // Invalid choice
                printf ("Invalid selection! Please type the number your choice and press Enter.\n");
                break;
		}
	}

	return (0);
}