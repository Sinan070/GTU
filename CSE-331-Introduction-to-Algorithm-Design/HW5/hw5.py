import random
import sys
def longestCommonString(words):
    if(len(words) == 1):
        return words[0]
    
    def helper(arrays):
        n = len(arrays)
        
        if (n == 1):
            return arrays[0]
        mid = int(n / 2)
        left = helper(arrays[:mid])
        right = helper(arrays[mid:])
        
        commonString=""
    
        for i in range(min(len(left), len(right))):
            if left[i] == right[i]:
                commonString += left[i]
                
            else:
                break
        return commonString

    return helper(words)





def findMaxProfitV1(array):
    maxProfit = -sys.maxsize -1
    minIndex = 0
    maxIndex = 0
    if(len(array) == 1):
        
        return 0,print(0)
        
    
    def helper(array):
        n = len(array)
        if((n == 1) | (n == 0)):
            return 0
        mid = int(n /2)
        helper(array[:mid])
        minPrice = min(array[:mid])
        nonlocal minIndex,maxIndex
        minIndex = indexOf(minPrice,array)
        helper(array[mid:])
        maxPrice = max(array[mid:])
        maxIndex = indexOf(maxPrice,array)
        nonlocal maxProfit
        profit = maxPrice - minPrice
        if(maxProfit < profit):
            maxProfit = profit
        return maxProfit
    helper(array)
    print("Output: Buy on Day{0} for {1} and sell on Day{2} for {3} profit = {4}"
    .format(minIndex,array[minIndex],maxIndex,array[maxIndex],maxProfit),end='\n')

def findMaxProfitV2(array):
    
    n = len(array)
    if(n == 1):
        return 0 ,print(0)
    maxProfit = -sys.maxsize -1
    minIndex = 0
    maxIndex = 0
    
    for i in range (n):
        buy = array[i]
        for j in range(i+1 ,n):
            sell = array[j]
            profit = int(sell - buy)
            if(maxProfit <  profit):
                minIndex =i
                maxIndex = j
                maxProfit = profit
      
    print("Output: Buy on Day{0} for {1} and sell on Day{2} for {3} profit = {4}"
    .format(minIndex,array[minIndex],maxIndex,array[maxIndex],maxProfit),end='\n')


def longest_increasing_sub_array(array):
    n = len(array)
    end = n
    result = [1]*n
    for i in range (n-1 , -1 , -1):
        for j in range (i+1,end):
            if(array[i] < array[j]):
                result[i] = max(result[i], 1+result[j])
            else :
                
                end = i+1
                break     
    return max(result)



def highestScore(matrix):
    rowNumber = len(matrix)
    colNumber = len(matrix[0])
    tempMatrix = [[0]* (colNumber+1) for i in range(rowNumber+1)]
    for i in range (1,rowNumber+1):
        for j in range(1,colNumber+1):
            tempMatrix[i][j] = matrix[i-1][j-1] 

    for i in range (1, rowNumber+1):
        for j in range (1, colNumber+1):
            
            if(tempMatrix[i-1][j] > tempMatrix[i][j-1]):
                max = tempMatrix[i-1][j]
            else:
                max =tempMatrix[i][j-1]
            tempMatrix[i][j] = tempMatrix[i][j] + max
    return tempMatrix[rowNumber][colNumber]




# this version is not gives optimal solution for all the matrix 
def highestScoreV2(matrix):
    rowLen = len(matrix)
    colLen = len(matrix[0])

    i = 0
    j = 0
    res = matrix[0][0]
    while((i != rowLen-1) & (j != colLen-1)):
        if(matrix[i+1][j] > matrix[i][j+1]):
            res += matrix[i+1][j]
            i += 1
        else :
            res += matrix[i][j+1]
            j += 1
    return res + matrix[rowLen-1][colLen-1]
        

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
    

def fillWithRandomArray():
    
    # generate a random array size
    array_size = random.randint(1, 8)

    # create an empty array
    array = [0 for _ in range(array_size)]

    # fill the array with random values
    for i in range(array_size):
        array[i] = random.randint(5, 12)

    # print the array
    print(array)
    return array


def indexOf(value,array):
    for i in range (len(array)):
        if(array[i] == value):
            return i
    return -1

def driver():
    words = [["compute", "compatible", "computer", "compare", "compactness"],
     ["programmable", "programming", "programmer", "programmatic", "programmability"],
     ["cse331","cse341","cse321","cse343"],
     ["commonString","commonStr","commonStri","commonSt","common"]
     ]

    matrix = [[1, 4, 5, 2, 4, 3, 6, 7, 1, 2, 3, 4, 7],
                [1, 2, 3, 4, 1, 2, 3, 5, 2, 3, 4],
                [5, 2, 3, 4, 1, 2, 3, 4, 5, 3, 4]]
    
    while(True):
        print("\nINPUTS SELECTION ARE RANDOMLY GENERATED IN EACH TURN\n")
        print("1-) Q1\n2-) Q2\n3-) Q3\n4-) Q4\n0-) Exit\n")
        select = int(input("Choice : "))
        if(select == 1):
            randNumber= random.randint(0,3)
            print("\nInput: ")
            print(words[randNumber],end='\n')
            print("Output : ")
            print(longestCommonString(words[randNumber]),end= '\n')


        elif(select == 2):
            tempArray = fillWithRandomArray()

            print("\nInput : ",tempArray,end='\n')
            print("Version1 : ")
            findMaxProfitV1(tempArray)
            print("Version2 : ")
            findMaxProfitV2(tempArray)


        elif(select == 3):
            randNumber = random.randint(0,2)

            print("\nInput : {0}".format(matrix[randNumber]),end='\n')
            print("Output : {0}".format(longest_increasing_sub_array(matrix[randNumber])),end='\n')

        elif(select == 4):
            print("\nVersion2 is not giving the optimal solution for all set\n")
            tempMatrix = fillWithRandom()
            print("Input : m = {0} n = {1}".format(len(tempMatrix),len(tempMatrix[0])),end='\n')
            print("\nMap: ",tempMatrix,end='\n')
            print("\nVersion1")
            print("Output :",highestScore(tempMatrix),end='\n')
            print("\nVersion2")
            print("Output: ",highestScoreV2(tempMatrix),end='\n')

        
        elif(select == 0):
            break
        
        else :
            print("\nPlease Enter Right Choice\n")






def main():
    driver()
    """
    matrix = [[25,30,25],[45,15,11],[1,88,15],[9,4,23]]
    words = ["compute", "compatible", "computer", "compare", "compactness"]
    print(longestCommonString(words))
    #divide(words)
    findMaxProfitV1([1, 4, 5, 2, 4, 3, 6, 7, 1, 2, 3, 4, 7])
    findMaxProfitV2([1, 4, 5, 2, 4, 3, 6, 7, 1, 2, 3, 4, 7])

    longest_increasing_sub_array([1, 4, 5, 2, 4, 3, 6, 7, 1, 2, 3, 4, 7])
    print(highestScore(matrix))
    print(highestScoreV2(matrix))
"""
main()
        





