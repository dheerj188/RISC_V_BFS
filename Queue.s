main:
li s0,0x2000 #use saved register s0 to store the start of queue.
li t0,23
sw t0,0(s0) #Start queue with some random element, say 23
li t1,0x0 #Define NULL to equal 0.
sw t1,4(s0) #Set the queue's end by declaring the last reference to be NULL.

jal x1,traverse #View the contents of the queue
#Let us now try to enqueue an element into the queue
li a0,12 #Load a value into the argument register and call enqueue sub-routine
jal x1,enqueue
jal x1,traverse
#Let us enqueue some more elements.
Addelems:
	li a0,10
	jal x1,enqueue
	li a0,14
	jal x1,enqueue
	li a0,17
	jal x1,enqueue
jal x1,traverse
#Let us now try to dequeue elements from the queue.
Rmvelems:
	jal x1,dequeue
	jal x1,dequeue
	jal x1,dequeue
jal x1,traverse
j Exit



enqueue:
	mv t1,s0 #Start of queue
	lw t2,4(s0) #next element of queue
	beq t2,x0,Append
	Loop1: 
		mv t1,t2
		lw t2,4(t2)
		bne t2,x0,Loop1 #Keep looping until t2 hits NULL.
	Append:
		addi t3,t1,8 #Mem location for the new element.
		sw t3,4(t1) #Make the previous last element point to this newly created element.
		sw a0,0(t3)
		sw x0,4(t3) #Make new element point to NULL.
		jalr x1 #Jump back to caller after adding new element.
		
dequeue:
	mv t1,s0 #Head of the queue
	lw t2,4(s0) #next element of the queue
	beq t1,x0,Exit_deq #If the queue is already empty, then exit.
	sw x0,0(t1) #Free up the element being removed
	sw x0,4(t1)
	mv s0,t2 #Head of the queue now points to the next element.
	Exit_deq:jalr x1

traverse:
	mv t1,s0
	Loop:  
		lw t0,0(t1) #t0 contains the element.
		lw t1,4(t1)
		bne t1,x0,Loop #Loop until NULL is reached
		jalr x1 #Jump back to caller after traversal

Exit:nop
