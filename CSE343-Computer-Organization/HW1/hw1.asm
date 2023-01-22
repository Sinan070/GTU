 .data
	
	array: .word # array stores elements to be operated.
		.space 100
		0 
	prompt1 : .asciiz "Please Enter the Number of Array and Divider (ex : 5 3) : " #prompt1 to take the user input
	prompt2 : .asciiz "Please Enter the Elements of Array  (ex: 1 2 3 4 5) : "   # #prompt2 to take the user input
	 
	inputBuffer : .space 200  # input buffer to be parsed into desired variables
	space : .asciiz " "  #space char
	
	numberStr : .space 3 # stored the parsed string to be convert integer
	i : .word 0   # global variable i to be used for iteration over array
	
	openP : .asciiz "("  #open phranthesis char
	closeP : .asciiz ")\n"  #close phranthesis char
	
	
	n : .word 0     #number of the array's element
	divider: .word 0 #desired divider 
	atoiNum : .word 0 #stores string that converted to  integer
	
	NULL: .asciiz "(null)"	#null 
	
		
		

.text

	main:
	
	# Print prompt 1 to get number and divider in string format
	li $v0 4
	la $a0 prompt1
	syscall
	
	# get number and divider in string format
	li $v0 8
	la $a0 inputBuffer
	li $a1 15
	syscall
	
	
	# get input buffer adress
	la $s1 inputBuffer
	
	# call parse procedur and store parsed num in numberStr	
	jal parse
	
	# call atoi procedure return converted string (store converted integer in $v0 register)
 	jal atoi
 	
 	#(store converted integer in n variable (length of the array))
	sw $v0 n 
 	
 	#call parse procedure to parse divider
	jal parse 
	#call atoi procedure to convert divider to integer format
 	jal atoi
 	
 	#(store converted integer in divider variable (store converted integer in $v0 register)
 	sw $v0 divider
	
	
	#prompt 2 to take input from use to get elements of array
	li $v0 4
	la $a0 prompt2
	syscall
			
	#take elements of array from user
	li $v0 8
	la $a0 inputBuffer
	li $a1 200
	syscall
	
	#load inputbuffer adress in s1 register
	la $s1 inputBuffer
		
	
	#counter begin from 0 to n
	addi $s3 $zero 0
	
	#store n in s4 register
	lw $s4 n
	
	
	
		while:
			# if (counter  > n ) go to whileEnd
			slt $t2 $s3 $s4
			beq $t2 $zero whileEnd
			
			# call parse procuder to parse element of array[counter]
			jal parse
			
			# call atio procedure to convert array[counter] to integer
			jal atoi
	
			# load adress of array[0]
			la $t2 array
			
			# find adress of array[counter]
			add $t3 $t5 $t2
			
			#store value of element that converted integer in array[counter]
			sw $v0 ($t3)
			
			#counter = counter +1
			addi $s3 $s3 1
			
			# multiply counter by 4 to get word from memeory and store result in $t5 reg
			sll $t5 $s3 2
			
			#jump while
			j while
	
						
	
	 
		whileEnd:
			jal findPair
			li      $v0, 10              # terminate program run and
    			syscall                      # Exit 
		
		
	
	
	#find paiar procedure. pair that their sum is dividable by divider
	
	findPair :
	
		li $t1 , 0 #i
		li $t2 , 0 #j
	
		lw $t0 , n #count
	
		LoopfindPair1:
		
			# if (i > n) go to endOFloop1
			slt $t3 , $t1 , $t0
			beq $t3 , $zero , endOFloop1
		
			# assign j=i
			add $t2 ,$t1 ,$zero 
									
				
			LoopfindPair2:
				# if (j>n) go to endOfllop2
				slt $t3 , $t2 , $t0
				beq $t3 , $zero ,endOFloop2
			

				beginif:
				
					#find array[j] adress
					sll $t3 , $t2 ,2
					la $t4 , array
					add $t4 , $t3 , $t4
	
					#find array[i] adress
					sll $t3 , $t1 ,2
					la $t5 , array
					add $t5 , $t3 , $t5
			
										
				 	#store array[i] and array[j] in $t4 and $t5 reg
					lw $t4 ($t4)
					lw $t5 ($t5)
				
					# sum = array[i] + array[j]	
					add $t6 , $t4 , $t5
					#store divider in $t7 reg
					lw $t7 , divider
				
					# remainder of sum / divider
					rem $t3 $t6 $t7
					
					# if sum % divider == 0 go to endif
					bne $t3 , $zero , endif
				
					
					# print pair ex:(1 2)
					li $v0 4
					la $a0 openP
					syscall 
					
					li $v0 , 1
					add $a0 , $t1 ,$zero
					syscall	
					
					li $v0 4
					la $a0 space
					syscall 
					
					
					li $v0 , 1
					add $a0 , $t2 , $zero
					syscall
		
					li $v0 4
					la $a0 closeP
					syscall
					
					li $v0 4
					la $a0 space
					syscall 
					
		
				endif:
					#j = j+1
					addi $t2 , $t2 , 1
					
					j LoopfindPair2
			endOFloop2:	
				#i = i+1	
				addi $t1 , $t1 , 1
				j LoopfindPair1
		endOFloop1:
			# jump to program counter
			jr $ra
	
			
			#find length of string
	lengthOfString:
	
		
		li $t0 0 #i
		
		la $t1 inputBuffer
		
		
		
		whileLoop :
					
		
			add $t3 $t1 $t0 #find adrees of inp[i]
		
			lb $t3 ($t3) #get char
			
			
			beq $t3 0 end
			
				
			addi $t0 $t0 1  
			
			
			j whileLoop
			 
		  end:
		  	
		  	addi $t0 $t0 -1
		  	add $v0 $t0 $zero #return length
		  	jr $ra 
		   
		  #parse string using delimeter space
	parse :	
		
		lw $t0 i
		
		la $t2 numberStr
		
		lb $t1 ($s1)
		
		bne $t1 10 beginWhile
		
		la $v0 NULL
		
		jr $ra
		
		beginWhile:
		    lb $t1 ($s1)
		    beq $t1 32 endWhile
		    beq $t1 10 endWhile    
		    add $t3 $t2 $t0
		    sb $t1 ($t3)
		    
		    addi $s1 $s1 1
		    addi $t0 $t0 1 
		    
		    j beginWhile
		
		endWhile:
		    addi $s1 $s1 1
		    lb $zero 1($t3)
		    la $v0 ($t2)
		    jr $ra
	
		
	 	#convert string to integer
	atoi:
		la $t0 numberStr
		addi $t1, $zero, 0 # t1 = res = 0
		
		whileAtoi:
			
			 
			lb $t2 ($t0)
			beq $t2, $zero, endAtoi
			addi $t2, $t2, -48 # convert to char to int		
			mul $t1, $t1, 10 # res *= 10
            		add $t1, $t1, $t2 # res += temp
			
			addi $t0, $t0, 1 # go to next char
			j whileAtoi
		endAtoi:
			add $v0 $t1 $zero
		
			jr $ra
			
			
				
	jr: 
		jr $ra
		
				
