import random


def play():
    global board
    board = ['1', '2', '3', '4', '5', '6', '7', '8', '9']
    count = 0
    print_board()
    name = input('Please enter your name: ')
    level = int(input('Enter 1 for easy mode and 2 for hard mode: '))

    while level is not 1 and level is not 2:
        level = int(input('Invalid input! \n Enter 1 for easy mode and 2 for hard mode: '))

    while True:
        if count >= 9:
            print('The game is draw')
            break

        user_input = int(input('Please Enter a number shown in the box: '))

        while user_input < 1 or user_input > 9 or board[user_input - 1] == '0' or board[user_input - 1] == 'X':
            user_input = int(input('Invalid input! Please Enter a number shown in the box: '))

        board[user_input - 1] = 'O'
        count += 1
        print_board()

        if check_winner() == True:
            print(name + ' is the winner')
            break


        if count >= 9:
            print('The game is draw')
            break


        print('Now computer turn')

        if level == 1:
            computer_input_easy()
        else:
            board[computer_input_hard()] = 'X'

        count += 1
        print_board()

        if check_winner() == True:
            print('Computer is the winner')
            break


def print_board():
    print(board[0] + ' | ' + board[1] + ' | ' + board[2])
    print('________')
    print(board[3] + ' | ' + board[4] + ' | ' + board[5])
    print('________')
    print(board[6] + ' | ' + board[7] + ' | ' + board[8])


def check_winner():
    for i in range(3):
        if board[3 * i + 0] == board[3 * i + 1] == board[3 * i + 2]:
            return True
        elif board[i] == board[i + 3] == board[i + 6]:
            return True
    if board[0] == board[4] == board[8] or board[2] == board[4] == board[6]:
        return True
    return False


def computer_input_easy():
    computer_input = random.choice(free_box())
    board[computer_input] = 'X'


def computer_input_hard():
    offense_move = smart_move('X','O')
    if offense_move[0] == True:
        return offense_move[1]
    defense_move = smart_move('O','X')
    if defense_move[0] == True:
        return defense_move[1]
    return random.choice(free_box())


def smart_move(val, val2):
    for i in range(3):
        index = lone_index(3 * i + 0, 3 * i + 1, 3 * i + 2, val, val2)
        if index[0] == True:
            return [True, index[1]]
        index = lone_index(i, i + 3, i + 6, val, val2)
        if index[0] == True:
            return [True, index[1]]

    index = lone_index(0, 4, 8, val, val2)
    if index[0] == True:
        return [True, index[1]]
    index = lone_index(2, 4, 6, val, val2)
    if index[0] == True:
        return [True, index[1]]
    return [False, index[1]]


def lone_index(a, b, c, val, val2):
    if (board[a] == val or board[b] == val or board[c] == val) and (board[a] != val2 and board[b] != val2 and board[c] != val2):
        if board[a] == board[b] == val:
                return [True, c]
        elif board[a] == board[c] == val:
                return [True, b]
        elif board[b] == board[c] == val:
                return [True, a]
        else:
            return [False, a]
    else:
        return [False, a]


def free_box():
    free_box_index = []
    for i in board:
        if i != 'O' and i != 'X':
            free_box_index.append(int(i)-1)

    return free_box_index

play()

