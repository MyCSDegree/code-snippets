# RPSLS

# import random for randrange
import random

# name_to_number (str)
# return: number in accordance to input str for rpsls
#         error on invalid input str
def name_to_number(str):
    if (str.lower() == 'rock'):
        return 0;
    elif (str.lower() == 'spock'):
        return 1;
    elif (str.lower() == 'paper'):
        return 2;
    elif (str.lower() == 'lizard'):
        return 3;
    elif (str.lower() == 'scissors'):
        return 4;
    else:
        print 'invalid input!'

# number_to_name (idx)
# return: returns str in accordance to idx for rpsls
def number_to_name(idx):
    if (idx == 0):
        return "rock"
    elif (idx == 1):
        return "Spock"
    elif (idx == 2):
        return "paper"
    elif (idx == 3):
        return "lizard"
    elif (idx == 4):
        return "scissors"

# rpsls
# main function which plays game with player_choice
def rpsls(player_choice):
    print '' # print blank line separating game
    
    print 'Player chooses ' + player_choice;
    player_number = name_to_number(player_choice);

    # comp_number b/w 0 and 4
    comp_number   = random.randrange(0,5)
    print 'Computer chooses ' + number_to_name(comp_number)

    # calculate diff
    diff = (player_number - comp_number) % 5;
    if (diff == 0): # this is a tie case
        print 'Player and computer tie!'
    elif (diff > 2): # this is 3,4 where computer wins
        print 'Computer wins!'
    else: # this is 1,2 where player wins
        print 'Player wins!'

rpsls('rock');
rpsls('Spock');
rpsls('paper');
rpsls('lizard');
rpsls('scissors');