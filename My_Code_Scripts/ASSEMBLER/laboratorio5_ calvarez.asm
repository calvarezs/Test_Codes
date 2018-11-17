# Programa Assembler Laboratorio 5
# Integrantes:  Carlos Alvarez
# Seccion L-4

      	.data    		# Informacion del menu
strttxt:.asciiz	"Bienvenido al programa\n"
menutxt:.asciiz	"Elije una opcion:\n  1: Obtener complemento\n  2: Suma binaria\n  3: Resta binaria\n  4: Salir del programa\n" 
      	.text			# Código main comienza a partir de aca
      	la   $a0, strttxt	# $a0 <-- direccion string START_TXT
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio
main:	la   $a0, menutxt	# $a0 <-- direccion string MENU_TXT
	addi $v0, $zero, 51 	# $v0 <-- 51 (Indicar servicio INPUT_DIALOG_INT)
	syscall 		# Ejecutar servicio
	beq  $a1, -2, exit	# si $a1 == -2  GOTO EXIT (si no se quiere ingresar datos ir a EXIT)
	bnez $a1, nomain	# Si $a1 !=  0  GOTO NOMAIN (a1 = 0 solo si el valor es ingresado correctamente)
	beq  $a0, 1, func1	# Si $a0 ==  1  GOTO FUNC_1 (calcular complemento) 
	beq  $a0, 2, func2	# Si $a0 ==  2  GOTO FUNC_2 (calcular suma binaria)
	beq  $a0, 3, func3	# Si $a0 ==  3  GOTO FUNC_3 (calcular resta binaria)
	beq  $a0, 4, exit	# Si $a0 ==  4  GOTO EXIT 
nomain:	jal  error 		# saltar a funcion de error 
	j    main		# Volver a main
	
###############################################
#Procedimiento complemento
	.data
inputc:	.asciiz "Ingrese un valor a obtener complemento\n"
txtc1:	.asciiz "Numero ingresado: "
txtc2:	.asciiz "Complemento a 1 : "
txtc3:	.asciiz "Complemento a 2 : "
saltoln:.asciiz "\n"
	.text
func1:	la   $a0, inputc	# $a0 <-- direccion string INPUT_C
	addi $v0, $zero, 51 	# $v0 <-- 51 (Indicar servicio INPUT_DIALOG_INT)
	syscall 		# Ejecutar servicio 
	beq  $a1, -2, main	# si $a1 == -2  GOTO MAIN (si no se quiere ingresar datos ir a MAIN)
	bnez $a1, nofunc1	# Si $a1 !=  0  GOTO NOFUNC1 (a1 = 0 solo si el valor es ingresado correctamente)
	add  $t7, $zero, $a0    # $t7 <-- $a0 (guardar valor a modificar)
	slt  $t2, $a0, $zero	# Si $a0 < 0;  so: $t2 <- 1 ;else: $t2 <- 0 (para el bit que almacena el signo)	
	abs  $t0, $a0		# $t0 <- |$a0|
	addi $t1, $zero, 2	# $t1 <- 2 (valor "constante" para division)
	add  $t4, $zero, $sp	# $t4 <- $sp (para resetear stack pointer mas tarde)
	addi $sp, $sp, -4	# $sp <- $sp - 4 (se avanza un espacio hacia abajo en el stack)
	addi $t6, $sp, -4	# $t6 <- $sp - 4 (se define la posicion final de la lista en stack)
	addi $t3, $zero, -1	# $t3 <- -1
	sw   $t3, 0($sp)	# stack_push($t3)  
	bnez $a0, else1		# si se ingresa 0 se inserta manualmente en stack
	addi $sp, $sp, -4	# $sp <- $sp - 4 (se avanza un espacio hacia abajo en el stack)
	sw   $a0, 0($sp)	# insercion manual de 0 en $sp[0]
else1:  nop			# NOP (ir a la siguiente linea, esta linea no es relevante salvo por su etiqueta)
loop1:	beqz $t0, noloop1	# Si $t0 == 0 GOTO NOLOOP1
	div  $t0, $t1		# LO <- $t0/2    HI <- $t0%2
	mfhi $t3	 	# $t3 <- HI
	addi $sp, $sp, -4	# $sp <- $sp - 4
	sw   $t3, 0($sp)	# stack_push($t3)
	mflo $t0		# $t0 <- LO
	j loop1			# GOTO LOOP1 (hasta que $t0 != 0)
noloop1:addi $t5, $sp, -4       # $t5 <- $sp - 4 (almacenar en $t5 la posición del primer valor en stack) 
	addi $sp, $sp, -8	# $sp <- $sp - 8 
	sw   $t2, 4($sp)	# stack_push($t2) 
	addi $t3, $zero, -1	# $t3 <- -1
	sw   $t3, 0($sp)	# stack_push($t3) 
	la   $a0, txtc1		# $a0 <-- direccion string TXTC_1
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio
	add  $a0, $zero, $t7	# $a0 <-- $t7 (asignar valor numerico para imprimir)
	addi $v0, $zero, 1 	# $v0 <-- 1 (Indicar servicio PRINT_INT)
	syscall 		# Ejecutar servicio
	la   $a0, saltoln	# $a0 <-- direccion string SALTO_LINEA
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio
	la   $a0, txtc2		# $a0 <-- direccion string TXTC_2
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio
loop2:	addi $sp, $sp, 4	# $sp <- $sp + 4 (desplazarse una posicion hacia arriba en el stack)
	lw   $t3, 0($sp)	# $t3 <- $sp[0] (leer el elemento al cual apunta el stack pointer)
	seq  $t0, $t3, -1	# si $t3 = -1; $t0 <- 1
	bnez $t0, noloop2	# si $t3 == -1 ($t0 = 1) terminar ciclo
	lw   $t2, 0($sp)	# Obtener valor en $sp[0]
	seq  $t2, $t2, $zero	# si $t2 == 0: $t2 <- 1 ; else $t2 <- 0
	sw   $t2, 0($sp)	# Invertir valor binario en lista
	j loop2			# repetir el ciclo
noloop2:add  $a0, $zero, $t5	# $a0 <- $t5 (se indica valor inicial para imprimir stack)
	jal printf		# imprimir desde $a0 hasta valor -1
	la   $a0, saltoln	# $a0 <-- direccion string SALTO_LINEA
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio			
	la   $a0, txtc3		# $a0 <-- direccion string TXTC_3
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio
	addi $sp, $t6, 4	# Ir al primer elemento insertado de la lista en stack 
loop3:	addi $sp, $sp, -4	# $sp <- $sp + 4 (desplazarse una posicion hacia arriba en el stack)
	lw   $t3, 0($sp)	# $t3 <- $sp[0] (leer el elemento al cual apunta el stack pointer)
	seq  $t0, $t3, -1	# si $t3 = -1; $t0 <- 1
	bnez $t0, noloop3	# si $t3 == -1 ($t0 = 1) terminar ciclo (si se termina la lista) 
	bnez $t3, else2		# si el valor en stack es igual a 0
	addi $t3, $zero, 1	# dicha posicion sera igual a 1	
	sw   $t3, 0($sp)	# insertar valor
	j noloop3		# terminar ciclo
else2:	sw   $zero, 0($sp)	# sino el valor en stack es igual a 0 
	j loop3			#repetir ciclo
noloop3:add  $a0, $zero, $t5	# $a0 <- $t5 (se indica valor inicial para imprimir stack)
	jal printf		# imprimir desde $a0 hasta valor -1
	la   $a0, saltoln	# $a0 <-- direccion string SALTO_LINEA
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio
	add  $t4, $zero, $sp	# $sp <- $t4 (reinciando stack pointer)
	j main			# Volver a la función principal
nofunc1:jal error 		# saltar a funcion de error 	 
	j func1			# Volver al incio de la funcion

###############################################
#Procedimiento suma binaria
	.data
inputs1:.asciiz "Ingrese el primer sumando\n"
inputs2:.asciiz "Ingrese el segundo sumando\n"
txts1:	.asciiz "\nNumero ingresado: " 
txts2:	.asciiz "\nSuma binaria: "
txts3: 	.asciiz "\nSuma decimal: "
	.text
func2:	add  $t9, $zero, $sp	# $t9 <- $sp (se guarda stack pointer para generar un reinicio mas tarde)
inpu1:	la   $a0, inputs1	# $a0 <-- direccion string INPUT_S1
	addi $v0, $zero, 51 	# $v0 <-- 51 (Indicar servicio INPUT_DIALOG_INT)
	syscall 		# Ejecutar servicio  			
	beq  $a1, -2, main	# si $a1 == -2  GOTO MAIN (si no se quiere ingresar datos ir a MAIN)
	bnez $a1, noinpu1	# Si $a1 !=  0  GOTO NO_INPUT_1 (a1 = 0 solo si el valor es ingresado correctamente)
	abs  $t0, $a0		# $t0 <- |$a0|	
	la   $a0, txts1		# $a0 <-- direccion string TXT_S1
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio
	add  $a0, $zero, $t0	# $a0 <-- $t0 (asignar valor numerico para imprimir)
	addi $v0, $zero, 1 	# $v0 <-- 1 (Indicar servicio PRINT_INT)
	syscall 		# Ejecutar servicio		
	add  $t1, $zero, $t0	# $t1 <- $a0 (Primer valor ingresado)
inpu2:	la   $a0, inputs2	# $a0 <-- direccion string INPUT_S2
	addi $v0, $zero, 51 	# $v0 <-- 51 (Indicar servicio INPUT_DIALOG_INT)
	syscall 		# Ejecutar servicio  			
	beq  $a1, -2, main	# si $a1 == -2  GOTO MAIN (si no se quiere ingresar datos ir a MAIN)
	bnez $a1, noinpu2	# Si $a1 !=  0  GOTO NO_INPUT_1 (a1 = 0 solo si el valor es ingresado correctamente)	
	abs  $t0, $a0		# $t0 <- |$a0|	
	la   $a0, txts1		# $a0 <-- direccion string TXT_S1
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio
	add  $a0, $zero, $t0	# $a0 <-- $t0 (asignar valor numerico para imprimir)
	addi $v0, $zero, 1 	# $v0 <-- 1 (Indicar servicio PRINT_INT)
	syscall 		# Ejecutar servicio			
	add  $t2, $zero, $t0	# $t2 <- $t0 (Segundo valor ingresado)	 
	addi $t0, $zero, 2	# $t0 <- 2 (valor temporalmente constante)
	add  $t5, $zero, $zero	# $t5 <- 0 (elemento carry)
	addi $sp, $sp, -4	# Desplazamiento stack pointer
	addi $t6, $zero, -1	# $t6 <- -1 
	sw   $t6, 0($sp)	# $sp <- -1 (elemento final lista)
	addi $t7, $zero, -1	# $t7 <- -1 (se define contador auxiliar)
loop4:  addi $t7, $t7, 1	# $t7 <- $t7+1 (auxiliar += 1)
	bnez $t1 else3		# si t1 != 0 GOTO ELSE3 
	bnez $t2 else3		# si t2 != 0 GOTO ELSE3 
	j noloop4		# sino terminar ciclo
else3:	div  $t1, $t0		# LO <- $t1/2    HI <- $t1%2
	mflo $t1		# $t1 <- LO
	mfhi $t3		# $t3 <- HI
	div  $t2, $t0		# LO <- $t2/2    HI <- $t2%2
	mflo $t2		# $t2 <- LO
	mfhi $t4		# $t4 <- HI
	add  $t6, $t3, $t4	# $t6 <- $t3 + $t4
	add  $t6, $t6, $t5	# $t6 <- $t3 + $t4 + carry($t5)
	bne  $t6, 0, elif1	# si $t6 == 0
	add  $t5, $zero, $zero	# entonces carry($t5) <- 0
	addi $sp, $sp, -4	# Desplazamiento stack pointer
	addi $t6, $zero, 0	# $t6 <- 0 
	sw   $t6, 0($sp)	# $sp <- 0 push(0)
	j loop4			# volver al ciclo
elif1:	bne  $t6, 1, elif2	# si $t6 == 1
	add  $t5, $zero, $zero	# entonces carry($t5) <- 0
	addi $sp, $sp, -4	# Desplazamiento stack pointer
	addi $t6, $zero, 1	# $t6 <- 1 
	sw   $t6, 0($sp)	# $sp <- 1 push(1)
	j loop4			# volver al ciclo
elif2:	bne  $t6, 2, else4	# si $t6 == 2
	addi $t5, $zero, 1	# entonces carry($t5) <- 1
	addi $sp, $sp, -4	# Desplazamiento stack pointer
	addi $t6, $zero, 0	# $t6 <- 0 
	sw   $t6, 0($sp)	# $sp <- 0 push(0)
	j loop4			# volver al ciclo
else4:	addi $t5, $zero, 1	# entonces carry($t5) <- 1
	addi $sp, $sp, -4	# Desplazamiento stack pointer
	addi $t6, $zero, 1	# $t6 <- 1 
	sw   $t6, 0($sp)	# $sp <- 1 push(1)
	j loop4			# volver al ciclo
noloop4:beqz $t5, else5		# si el carry no es 0 ($t5 != 0) 
	addi $sp, $sp, -4	# Desplazamiento stack pointer
	addi $t6, $zero, 1	# $t6 <- 1 
	sw   $t6, 0($sp)	# entonces se inserta un 1 extra en la lista
	addi $t7, $t7, 1	# $t7 <- $t7 + 1
else5:	la   $a0, txts2		# $a0 <-- direccion string TXT_S2
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio 		
	add  $a0, $zero, $sp	# $a0 <- $sp (se indica el incio de la lista) 
	jal printf		# se imprime la serie de numeros
	add  $t1, $zero, $zero	# $t1 <- 0 (se define $t1 como resultado numerico)
	addi $t2, $zero, 1	# $t2 <- 1 (se define $t2 como valor constante temporalmente)
loop5:	lw   $t0, 0($sp)	# $t0 <- $sp[0] (se lee en $t0 el primer valor de la lista)
	beq  $t0, -1, noloop5	# mientras $t0 != -1
	addi $sp, $sp, 4	# #sp <- $sp + 4 (se sube una posicion a la lista)
	addi $t7, $t7, -1	# $t7 <- $t7 - 1 (se disminuye el contador)
	bne  $t0, 1, else6	# si el valor en lista stack es igual a 1
	sllv $t3, $t2, $t7	# se eleva el contenido de $t2 en $t7 veces
	add  $t1, $t1, $t3	# se añade el valor de $t3 al valor en $t1
else6:	j loop5			# repetir el ciclo
noloop5:la   $a0, txts3		# $a0 <-- direccion string TXT_S3
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio
	add  $a0, $zero, $t1	# $a0 <-- $t1 (asignar valor numerico para imprimir)
	addi $v0, $zero, 1 	# $v0 <-- 1 (Indicar servicio PRINT_INT)
	syscall 		# Ejecutar servicio																																						
	add  $sp, $zero, $t9	# $sp <- $t9 (reinicio efectivo del stack pointer)
	j main			# terminar procedimiento (GOTO MAIN)
noinpu1:jal  error		#Indicar error al usuario
	j inpu1			#Volver a pedir dato
noinpu2:jal  error		#Indicar error al usuario
	j inpu2			#Volver a pedir dato	 
				
###############################################
#Procedimiento resta binaria
	.data
inputr1:.asciiz "Ingrese el minuendo\n"
inputr2:.asciiz "Ingrese el sustraendo\n"
txtr1:	.asciiz "\nNumero ingresado: " 
txtr2:	.asciiz "\nResta binaria: "
txtr3: 	.asciiz "\nResta decimal: "
negsim:	.asciiz "-"
	.text 
func3:	add  $t9, $zero, $sp	# $t9 <- $sp (se guarda stack pointer para generar un reinicio mas tarde)
inpu21:	la   $a0, inputr1	# $a0 <-- direccion string INPUT_R1
	addi $v0, $zero, 51 	# $v0 <-- 51 (Indicar servicio INPUT_DIALOG_INT)
	syscall 		# Ejecutar servicio  			
	beq  $a1, -2, main	# si $a1 == -2  GOTO MAIN (si no se quiere ingresar datos ir a MAIN)
	bnez $a1, noinpu21	# Si $a1 !=  0  GOTO NO_INPUT_1 (a1 = 0 solo si el valor es ingresado correctamente)	
	add  $t1, $zero, $a0	# $t1 <- $a0 (Primer valor ingresado)
	la   $a0, txtr1		# $a0 <-- direccion string TXT_R1
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio
	add  $a0, $zero, $t1	# $a0 <-- $t1 (primer valor ingresado para imprimir por pantalla)
	addi $v0, $zero, 1 	# $v0 <-- 1 (Indicar servicio PRINT_INT)
	syscall 		# Ejecutar servicio		
inpu22:	la   $a0, inputr2	# $a0 <-- direccion string INPUT_R2
	addi $v0, $zero, 51 	# $v0 <-- 51 (Indicar servicio INPUT_DIALOG_INT)
	syscall 		# Ejecutar servicio  			
	beq  $a1, -2, main	# si $a1 == -2  GOTO MAIN (si no se quiere ingresar datos ir a MAIN)
	bnez $a1, noinpu22	# Si $a1 !=  0  GOTO NO_INPUT_1 (a1 = 0 solo si el valor es ingresado correctamente)	
	add  $t2, $zero, $a0	# $t2 <- $a0 (Segundo valor ingresado) 
	la   $a0, txtr1		# $a0 <-- direccion string TXT_R1
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio
	add  $a0, $zero, $t2	# $a0 <-- $t2 (asignar segundo valor ingresado para imprimir)
	addi $v0, $zero, 1 	# $v0 <-- 1 (Indicar servicio PRINT_INT)
	syscall 		# Ejecutar servicio 
	addi $sp, $sp, -8	# Se avanza stack pointer para almacenar 2 palabras
	addi $t3, $zero, -1	# $t3 <- -1 (se almacena el final del arreglo a construir)
	sw   $t1, 4($sp)	# se ingresa el primer valor ingresado en stack 
	sw   $t3, 0($sp)	# se ingresa un -1 en stack
	add  $t1, $zero, $t2	# $t1 <- $t2 (se trabajara con el segundo valor ingresado)
	slt  $t8, $zero, $t1	# si $t1 < 0 se guardara un 1 como valor de signo
	abs  $t1, $t1		# $t1 <- |$t1|
	addi $t0, $zero, 2	# $t0 <- 2 (pseudo constante)
	addi $t6, $zero, 1	# $t6 <- 1 (ingresar numero al final)
rloop1:	div  $t1, $t0		# LO <- $t1/2    HI <- $t1%2
	mflo $t1		# LO <- $t1
	mfhi $t2		# HI <- $t2		
	bnez $t2, rtrue2	# si $t2 != 0 GOTO R_TRUE_2
	addi $sp, $sp, -4	# sino avanzar un espacio en el stack pointer
	sw   $t2, 0($sp)	# guardar $t2 en stack ($sp[0] <- 0)
	jal  rnloop1		# salto temporal a R_NO_LOOP_1
	j    rloop1		# al volver del salto saltar a R_LOOP_1 (recomenzar ciclo)
rtrue2:	addi $sp, $sp, -4	# avanzar un espacio en el stack pointer
	sw   $t2, 0($sp)	# guardar $t2 en stack ($sp[0] <- 1)
	jal  rnloop1		# salto temporal a R_NO_LOOP_1
rloop2:	div  $t1, $t0		# al volver del salto realizar division LO <- $t1/2    HI <- $t1%2
	mflo $t1		# LO <- $t1
	mfhi $t2		# HI <- $t2
	seq  $t2, $t2, $zero	# si $t2 == 0 ; $t2 = 1; sino $t2 = 0
	addi $sp, $sp, -4	# avanzar un espacio en el stack pointer
	sw   $t2, 0($sp)	# guardar $t2 en stack 
	jal  rnloop1		# salto temporal a R_NO_LOOP_1
	j    rloop2		# al volver del salto saltar a R_LOOP_2 (recomenzar ciclo)
rnloop1:beqz $t1, rtrue3	# si $t1 == 0 salir ciclo (GOTO R_TRUE_3) 				
	jr   $ra		# sino volver a la instruccion de origen
rtrue3: addi $sp, $sp, -4	# avanzar un espacio en el stack pointer
	sw   $t8, 0($sp)	# guardar $t8 en stack   
	add  $t8, $sp, $zero	# guardar la primera posicion del arreglo  
	add  $sp, $zero, $t9	# reiniciar sp 
	addi $sp, $sp, -4	# avanzar un espacio de palabra en stack
	lw   $t1, 0($sp)	# obtener primer valor ingresado ($t1 <- sp[0])
	addi $sp, $sp, -8	# avanzar dos espacios en sp (ultimo valor del arreglo)
	slt  $t7, $t1, $zero	# si $t1 < 0 se guardara un 1 como valor de signo  
	lw   $t5, 0($t8)	# se guarda el signo del segundo valor
	addi $t5, $zero, -1	# $t5 <- -1
	sw   $t5, 0($t8)        # se ingresa -1 en la primera posicion del arreglo
	add  $t7, $t7, $t5	# se suman los signos binarios de ambos valores
	abs  $t1, $t1		# $t1 <- |$t1|
	add  $t3, $zero, $zero	# $t3 <- 0 (inicio carry)
rloop3:	div  $t1, $t0		# LO <- $t1/2    HI <- $t1%2
	mflo $t1		# LO <- $t1
	mfhi $t2		# HI <- $t2						
	lw   $t6, 0($sp)	# leer el ultimo valor del arreglo en stack			
	bne  $t6, -1, rtrue4	# si el valor leido no es -1 continuar
	addi $t6, $zero, 1	# se escribe un 1 en esa posicion
	sw   $t6, 0($sp)	# se escribe un 1 en esa posicion 
	addi $sp, $sp, -4	# se avanza el stack pointer
	sw   $t5, 0($sp)	# se escribe -1 en la nueva posicion
	addi $sp, $sp, 4	# se devuelve el stack pointer a su posicion original						
rtrue4:	add  $t4, $t6, $t2	# se suman los bits en ambos numeros
	add  $t4, $t4, $t3	# se le suma el carry	
	bne  $t4, 3, relif1	# si la sumatoria es igual a 3
	addi $t3, $zero, 1	# el carry es igual a 1
	sw   $t3, 0($sp)	# el resultante es igual a 1
	j rcont2		# continuar con la ejecucion
relif1:	bne  $t4, 2, relif2	# si la sumatoria es igual a 2
	addi $t3, $zero, 1	# el carry es igual a 1
	sw   $zero, 0($sp)	# el resultante es igual a 0
	j rcont2		# continuar con la ejecucion
relif2: bne  $t4, 1, relif3	# si la sumatoria es igual a 1
	add  $t3, $zero, $zero	# el carry es igual a 0
	sw   $t4, 0($sp)	# el resultante es igual a 1
	j rcont2		# continuar con la ejecucion
relif3: nop		        # si la sumatoria es igual a 0 (como es la ultima opcion posible no hay evaluacion)
	add  $t3, $zero, $zero	# el carry es igual a 0
	sw   $zero, 0($sp)	# el resultante es igual a 0	
	j rcont2		# continuar con la ejecucion																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																		
rcont2:	beqz $t1, rtrue5	# si $t1/2 != 0	
	addi $sp, $sp, -4	# avanzar stack pointer 					
	j rloop3		# repetir ciclo
rtrue5:	addi $sp, $sp, -4	# retroceder stack pointer 
	add  $t4, $t7, $t3	# sino se suman los valores de signo
	add  $t8, $zero, $sp	# se guarda la primera posicion del arreglo
	bnez $t4, relif4	# si la sumatoria es igual a 0 ingresar 0
	sw   $zero, 0($sp)	# ingreso de 0
	j rcont4		# se saltan las siguientes operaciones
relif4:	bne $t4, 2, rcont3	# si la sumatoria es igual a 2 ingresar 0
	sw   $zero, 0($sp)	# ingreso de 0
	j rcont4		# se saltan las siguientes operaciones 
rcont3:	addi $t4, $zero, 1	# si no se define $t4 a 1
	sw   $t4, 0($sp)	# ingreso de $t4 	
rcont4:	la   $a0, txtr2		# $a0 <-- direccion string TXT_R2
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio
	add $a0, $zero, $sp	# se ingresa la posicion del primer valor de la lista para su impresion					
	jal printf		# Imprimir listado
	la   $a0, txtr3		# $a0 <-- direccion string TXT_R3
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio
	lw   $t0, 0($sp)	# se lee el primer valor del arreglo
	beqz $t0, relse5	# si el valor es igual a 1
	la   $a0, negsim	# $a0 <-- direccion string negsim
	addi $v0, $zero, 4 	# $v0 <-- 4 (Indicar servicio PRINT_STRING)
	syscall 		# Ejecutar servicio																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																											
relse5:	addi $t0, $zero, -1	# reemplazar el valor con -1
	sw   $t0, 0($sp)	# reemplazar el valor con -1
	addi $sp, $t9, -12	# ir a la ultima posicion del arreglo
	addi $t4, $zero, 1	# $t4 <- 1 
	add  $t0, $zero, $zero	# se define un contador en 0
	add  $t1, $zero, $zero	# se define un acumulador en 0
loop7:	lw   $t2, 0($sp)	# leer el primer valor en arreglo
	beq  $t2, -1, noloop7	# mientras no se encuentre un valor -1
	beqz $t2, relse6	# si el valor en dicha posicion es 1
	sllv $t3, $t4 ,$t0	# se eleva 1 a dos por la cantidad de veces el contador
	add  $t1, $t1, $t3	# se añade el valor al acumulador
relse6:	addi $t0, $t0, 1	# se incrementa el contador
	addi $sp, $sp, -4	# se avanza el stack pointer
	j loop7			# se repite el ciclo 
noloop7:add  $a0, $zero, $t1	# $a0 <- $t1
	addi $v0, $zero, 1    	# $v0 <- 1 (Indicar servicio PRINT_INT)
      	syscall               	# Ejecutar Servicio 																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																															
	add  $sp, $zero, $t9	# $sp <- $t9 (reinicio efectivo del stack pointer)
	j main			# terminar procedimiento (GOTO MAIN)
noinpu21:jal  error		# Indicar error al usuario
	j inpu21		# Volver a pedir dato
noinpu22:jal  error		# Indicar error al usuario
	j inpu22		# Volver a pedir dato	
	
############################################### 		
#Procedimiento ERROR
	.data
failtxt:.asciiz "Valor no valido.\nPor favor intente nuevamente.\n"
      	.text	 		
error:	la   $a0, failtxt	# $a0 <-- direccion string FAIL_TXT
	add  $a1, $zero, $zero 	# $a1 <-- 0 (indica mensaje de error)
	addi $v0, $zero, 55 	# $v0 <-- 55 (Indicar servicio MESSAGE_DIALOG) 
	syscall 		# Ejecutar servicio
	jr   $ra  		# Volver a la ejecucion anterior
		 			 		
###############################################	 		
#Procedimiento EXIT
	.data
byetxt:	.asciiz "Que tenga una buen dia\n"
	.text
exit:	la   $a0, byetxt	# $a0 <-- direccion string BYE_TXT
	addi $a1, $zero, 1 	# $a1 <-- 1 (indica mensaje de informacion)
	addi $v0, $zero, 55 	# $v0 <-- 55 (Indicar servicio MESSAGE_DIALOG)
	syscall 		# Ejecutar servicio 	
	addi $v0, $zero, 10	# $v0 <-- 10 (Indicar servicio de Salida)
      	syscall			# Ejecutar Servicio
      	 	
###############################################	 
#Procedimiento imprimir stack hasta elemento negativo
#se presume que en $a0 se encuentra una cadena de valores no vacia terminada en valor negativo
printf: add  $t0, $zero, $a0  	# $t0 <- $a0 ($a0 es requerido mas tarde)	
looprin:lw   $a0, 0($t0)      	# $a0 <- $t0[0] (se obtiene el primer valor en stack)
	slt  $t1, $a0 ,$zero    # si $a0 < 0 ; so $t1 = 1; else $t1 = 0
	beq  $t1, 1, noprint	# (si $t0 negativo finalizar)
      	addi $v0, $zero, 1    	# $v0 <- 1 (Indicar servicio PRINT_INT)
      	syscall               	# Ejecutar Servicio 
      	addi $t0, $t0, 4      	# Avanzar una posicion en la lista
      	j looprin             	# GOTO LOOP_PRINT (hasta que $t0 < 0; vale decir $t1 == 1)
noprint:jr   $ra              	# volver al procedimiento anterior


