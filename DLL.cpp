/*
 * DLL.cpp
 *
 *  Created on: Oct 17, 2021
 *      Author: manas
 */


#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <ostream>
#include <stdlib.h>
using namespace std;


	DLL::DLL(){  // constructor - initializes an empty list
		last = NULL;
		first = NULL;
		numSongs = 0;
	}
	DLL::DLL(string t, string l, int m, int s){  // constructor, initializes a list with one new node with data x
		DNode *n = new DNode (t,l,m,s);
		first = n;
		last = n;
		numSongs=1;
	}
	void DLL::push(string t, string a, int m, int s){
	/*This pushes a new node onto the end of the list. If there are no nodes in the list, it creates the
	first node and adds it. Otherwise it places a new node onto the end of the list. t is the song�s
	title,a is the song�s artist, m is the number of minutes the song runs for, and s is the number of
	seconds the song runs for
	For testing: When my readList method in Playlist.hpp is called, it continuously calls the list�s push
	method. So if this method reads in the list, and then print it out successfully, that is sufficient for
	testing. Although for your purposes, it will be notably easier to test once you�ve written printList()
	(explained below).
	*/
		if(numSongs==0){
			first = new DNode(t,a,m,s);
			last = first;
			numSongs++;
		}
		else{
			DNode *z = new DNode(t,a,m,s);
		//If there are no nodes in the list, it creates the first node and adds it
			z->song->printSong();
			last->next = z;
			z->prev = last;
			z->next = NULL;
			last = z;
			numSongs+=1;
		}
		return;

	}
	void DLL::printList(){
		/*This method should print out the list. Note that I have included a method for printing out each
		song object in the song class definitions, called printSong(). If you call that, the songs will
		printed out in the format you see in the output
		For testing: after every action you take, printList is called from the Playlist method definitions. Thus this
		will be tested automatically as we (and you) run the code.*/
		DNode *temp;
		for (temp = first;  temp != NULL; temp = temp->next)  {
			temp->song->printSong();

		}
		return;
	}

	int DLL::remove(string t){
		/*This method finds the song with the title s and removes the node that holds that song from the
		list. I have this method print the line,
		Removing: songtitle, songartist���������..songmin:songsec
		In other words, I have it print the song it is removing.
		(Note: if the song is the data in the last node in the list, this method calls the pop method (as
		described below).
		For testing: We will use option 2 in the playlist with 4 different songs including the first song, a random
		song (chosen in the middle somewhere), and the last song twice.*/
		DNode *tmp;
		int index = 0;
		       for (tmp = first;  tmp != NULL; tmp = tmp->next)  {
				if (tmp->song->title== t) {
					/*cout << 'Removing: '<< tmp->song->printSong();
					cout << endl;*/
					if (tmp->prev== NULL) {
						first = tmp->next;

		 			}
					else if(tmp->next== NULL) {
						*pop();
		      			}
					else { /* Remove from middle */
		       				tmp->prev->next=tmp->next; /* Fix previous node's next to  skip over the removed node.  */
		       				tmp->next->prev = tmp->prev; /* Fix next node's prev to skip over the removed node. */
		     		 	}
		      			delete tmp;
				 }
				index++;
		  	}
		  	return index;


	}
	Song *DLL::pop(){
	 	/*This pops the last node off the list. If there is only one node on the list, it resets first and last to
		NULL and the numSongs field to 0. It returns a song object.
		(Honestly, I barely used pop in this project. I had it called when I removed the last node from
		the list using a special case in my remove method. I am having you write it because it is just so
		fundamental to linked lists that I would be remiss as a teacher if I didn�t have you write this).
		For testing: I am happy with your calling it successfully from your remove method*/
		Song *x = NULL;
		if(numSongs == 1){
			x=first->song;
			first = NULL;
			last = NULL;
			numSongs =0;
		}
		else{
			DNode *t = last;
			x = t->song;
			last = last -> prev;
			delete t->song;
			delete t;
			last->next = NULL;
			numSongs--;
		}

		return x;

	}

	void DLL::moveUp(string t){
		/*This method moves a song up one in the playlist. For instance, if you had the following:
		Punching in a Dream, The Naked And Famous................3:58
		Harder To Breather, Maroon 5................2:52
		Where the Rivers Flow, Sons of Maria................3:O3
		Still Not a Player, Big Pun Joe................3:56
		Train, Brick+Mortar................3:O5

		And the song was �Still Not a Player�, the result would be:
		Punching in a Dream, The Naked And Famous................3:58
		Harder To Breather, Maroon 5................2:52
		Still Not a Player, Big Pun Joe................3:56
		Where the Rivers Flow, Sons of Maria................3:O3
		Train, Brick+Mortar................3:O5

		If you move the first song up, it will be moved to the end of the list as follows:
		Punching in a Dream, The Naked And Famous................3:58
		Harder To Breather, Maroon 5................2:52
		Still Not a Player, Big Pun Joe................3:56
		Where the Rivers Flow, Sons of Maria................3:O3
		Train, Brick+Mortar................3:O5

		Moving �Punching in a Dream� up one would result in:
		Harder To Breather, Maroon 5................2:52
		Still Not a Player, Big Pun Joe................3:56
		Where the Rivers Flow, Sons of Maria................3:O3
		Train, Brick+Mortar................3:O5
		Punching in a Dream, The Naked And Famous................3:58
		For testing: We will run 4 tests, including moving the last song up, the first song up twice, and a random middle
		song of our choice!*/
		DNode *x;
		if(t==first->song->title){
			DNode *ptemp = last;
				for(DNode *e = last->prev;e!=NULL;e=e->prev){
						Song *a = e->song;
						e->song = ptemp->song;
						ptemp->song = a;
						}
		}
		else{
			for (x = first->next;  x != NULL; x = x->next)  {
				if(t==x->song->title){
					Song *v = x->prev->song;
					x->prev->song = x->song;
					x->song = v;
				}
			}
		}
		return;

	}

	void DLL::moveDown(string t){
		/*This method moves a song down one in the playlist. For instance, if you had the following:
		Punching in a Dream, The Naked And Famous................3:58
		Harder To Breather, Maroon 5................2:52
		Where the Rivers Flow, Sons of Maria................3:O3
		Still Not a Player, Big Pun Joe................3:56
		Train, Brick+Mortar................3:O5
		And the song was �Harder To Breather�, the result would be:
		Punching in a Dream, The Naked And Famous................3:58
		Where the Rivers Flow, Sons of Maria................3:O3
		Harder To Breather, Maroon 5................2:52
		Still Not a Player, Big Pun Joe................3:56
		Train, Brick+Mortar................3:O5
		If you move the last song (�Train�)down, it will be moved to the beginning of the list as follows:
		Train, Brick+Mortar................3:O5
		Punching in a Dream, The Naked And Famous................3:58
		Where the Rivers Flow, Sons of Maria................3:O3
		Harder To Breather, Maroon 5................2:52
		Still Not a Player, Big Pun Joe................3:56
		For testing: We will run 4 tests, including moving the first song down, the last song down twice, and a random
		middle song of our choice down!*/
		DNode *x;
				if(t==last->song->title){
					DNode *ptemp = first;
						for(DNode *e = first->next;e!=NULL;e=e->next){
								Song *a = e->song;
								e->song = ptemp->song;
								ptemp->song = a;
										}
				}
				else{
					for (x = last->prev;  x != NULL; x = x->prev)  {
						if(t==x->song->title){
							Song *v = x->next->song;
							x->next->song = x->song;
							x->song = v;
						}
					}
				}
				return;

	}

	void DLL::makeRandom(){
		/*This method randomly shuffles the songs so that they are in a different, random order.
		For testing: Randomly shuffle the list twice using the option 5 in the Playlist interface (This
		option automatically calls the printList method for the list, so you can see your randomly
		ordered list)*/
		DNode *m;
		for (m = first;  m != NULL; m = m->next)  {
			int a = rand()%numSongs;
			int o=0;
			for(DNode *u=first;o<=a;u=u->next){
				if(o==a){
					Song *v = m->song;
					m->song = u->song;
					u->song = v;
				}
				o++;
			}
		}

		return;
	}


	void DLL::listDuration(int *tm, int *ts){
		/*This method traverses the list and adds up the minutes and seconds of each song to determine the total
	duration of the list (i.e., all your songs in the playlist). Note that it uses call by pointer to update the
	minutes and the seconds for outside of the method.
	For Testing: We will run this using option 7 in the Playlist interface, so check to confirm it is correct.
	When you create a brand new playlist (described below) you should run this again and double-check the
	time to make sure it is correct.*/
		for (DNode *tmp = first;  tmp != NULL; tmp = tmp->next)  {
			*tm+=tmp->song->min;
			*ts+=tmp->song->sec;
		}

		return;
	}
	DLL::~DLL(){
/*If you write the destructor for the linked list correctly, this will work. So this involves writing the
destructor for the linked list, deleting all the nodes in the linked list and resetting the linked list�s fields.
For Testing: We will be using Option 6 in the Playlist�s interface. For that, the destructor will be called
and you will be asked to enter the name of a new text file with a new set of songs to be read into a list.
Note: after you do this, you should use the option 7 to get a new list duration, and double-check it.*/
		for (DNode *tmp = first;  tmp != NULL; tmp = tmp->next)  {
			delete tmp->song;
			delete tmp;
		}

		first = NULL;
		last = NULL;
		numSongs = 0;
	}








