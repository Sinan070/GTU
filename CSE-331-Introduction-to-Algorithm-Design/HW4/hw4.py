#Q1
import timeit
import random

def maxPathFinding(grid):
    n = len(grid)
    m = len(grid[0])
    maxPath = 0
    path = [[]]
    res = [[]]
    
    def findPath(i,j,pathLength):
        if((i == n) | (j==m)) :
            return 
        pathLength = pathLength+grid[i][j]
        path.append([i,j])
        if( (i == n-1) & (j == m-1)):
            nonlocal maxPath
            nonlocal res
            if( maxPath < pathLength):
                res.clear()
                maxPath = pathLength    
                for list in path:
                    res.append(list[:])

    
        findPath(i,j+1,pathLength)
        findPath(i+1,j,pathLength)
        path.pop()
    
    findPath(0,0,0)
    print("Path->> ", res,"\n")
    print("Result->> ",maxPath,"\n")


#Q2

def partitioning(first, last,array):
    up = first
    down = last
    flag = True
    pivot = array[first]
    while(flag):
        while((up < down) & (pivot >= array[up])):
            up +=1
        while((pivot < array[down])):
            down -=1
        if(up < down):
            temp = array[up]
            array[up] = array[down]
            array[down] = temp
        else :flag = False

    temp = array[down]
    array[down] = array[first]
    array[first] = temp
    return down
    
def findMedian(array):
    a = -1 
    b = -1
    lenght = len(array)
    mid = int(lenght /2)
    def helper(start , end):
        if(start <= end ):
            pivot = partitioning(start,end,array)
            nonlocal a
            nonlocal b
            if(pivot == mid):
                a = array[pivot]
                if(b!=-1):
                    return
            elif(pivot == mid -1):
                b = array[pivot]
                if(a!=-1):
                    return
            if(pivot >= mid):
                helper(start,pivot-1)
            elif(pivot < mid):
                helper(pivot+1,end)         
        
    if(lenght %2):
        helper(0,lenght-1)
        return a
    
    else:
        helper(0,lenght-1)
        return (a+b)/2

#q3

def findSurvivor(n):
    
    players = [i for i in range(1, n+1)]

    def helper(start,end):
        if (start == end):
            return players[start]

        mid = (start + end) // 2
        left = helper( start, mid)
        right = helper( mid + 1, end)

        mid = end - start + 1
        if mid % 2 == 0:    return left
        else:   return right
        
    print(helper(0,n-1))       



def findSurviviorCLL(n):
    list = CircularLinkedList()
    
    for i in range (n):
        list.add(i+1)

    node = list.root

    while(node != node.next):
        node.next = node.next.next
        node = node.next
    
    return node.data


#circular linked list class
class CircularLinkedList:
    def __init__(self):
        self.root = None
        self.last = None
    class Node:
        def __init__(self,data):
            self.data = data
            self.next = None

    def add(self,data):
        if(self.root == None):
            self.root = self.Node(data)
            self.root.next = self.root
            self.last = self.root
        else:
            self.last.next = self.Node(data)
            self.last.next.next = self.root
            self.last =self.last.next
        
    
    def print(self):
        if(self.root == None): return
        else:
            iter = self.root
            while(iter.next != self.root):
                print(iter.data)
                iter = iter.next
            print(iter.data)


#random filling functions
def fillWithRandom():

    max_num_rows = 5
    max_num_cols = 5

    # generate random row and column sizes
    num_rows = random.randint(1, max_num_rows + 1)
    num_cols = random.randint(1, max_num_cols + 1)

    # create an empty matrix
    matrix = [[0 for _ in range(num_cols)] for _ in range(num_rows)]

    # fill the matrix with random integer values
    for i in range(num_rows):
        for j in range(num_cols):
            matrix[i][j] = random.randint(0, 60)

    return matrix
    # print the matrix
    #for row in matrix:
    #print(row)

def fillWithRandomArray():
    
    # generate a random array size
    array_size = random.randint(1, 10)

    # create an empty array
    array = [0 for _ in range(array_size)]

    # fill the array with random values
    for i in range(array_size):
        array[i] = random.randint(0, 15)

    # print the array
    print(array)
    return array


#driver
def driver():
    while(True):
        print("INPUTS ARE RANDOMLY GENERATED IN EACH TURN\n")
        print("1-) Q1\n2-) Q2\n3-) Q3\n0-) Exit\n")
        select = int(input("Choice : "))
        if(select == 1):
        
            grid = fillWithRandom()
            print("Grid\n",grid,"\n")
            maxPathFinding(grid)

    

        elif(select == 2):
            array = fillWithRandomArray()
            print("Result ->> " ,findMedian(array),"\n")
            
        
        elif(select == 3):
            while(True):
                randomSize = random.randint(1,10)
                select2 = int(input("1-) Linear Time\n2-) Logarithmic Time\n0-)Back to the Menu\n"))
                print("Number of players : ",randomSize,"\n")
                if(select2 == 1):
                    print("Result ->>> ",findSurviviorCLL(randomSize),"\n")
                elif(select2 == 2):
                    print("Result ->>> ",findSurviviorCLL(randomSize),"\n")
                elif(select2 == 0):
                    break
                else:
                    print("Please Enter Right Choice\n")


        elif(select == 0):
            break
        
        else :
            print("\nPlease Enter Right Choice\n")


#main
def main():
    driver()


#main call
main()