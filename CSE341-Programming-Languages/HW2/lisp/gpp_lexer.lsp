
;KEYWORD KEY-VALUE
(defvar keywordMap (pairlis '("and"  "or"  "not" "equal" "less" "nil" "list" "append"
"concat" "set" "deffun" "for" "if" "exit" "load" "disp" "true" "false") 
'("KW_AND" "KW_OR" "KW_ NOT" "KW_EQUAL" "KW_LESS" "KW_NIL" "KW_LIST"
"KW_APPEND" "KW_CONCAT" "KW_SET" "KW_DEFFUN" "KW_FOR" "KW_IF"
"KW_EXIT" "KW_LOAD" "KW_DISP" "KW_TRUE" "KW_FALSE")))



; OPERATION KEY-VALUE
(defvar opMap (pairlis'("+" "-" "/" "*" "(" ")" "**" ",")
'("OP_PLUS" "OP_MINUS" "OP_DIV" "OP_MULT" "OP_OP" "OP_CP"
"OP_DBLMULT" "OP_COMMA")
))








;split space seperated word to tokens
(defun splitToken (string &key (delimiter  #'isPharantesis)
                                         (keep-delimiters t)
                                    &aux (l (length string)))


  (loop for start = 0 then (1+ pos)
        for pos   = (position-if delimiter string :start start)

        ; no more delimiter found
        when (and (null pos) (not (= start l)))
        collect (subseq string start)

        ; while delimiter found
        while pos
        

        ;  some content found
        when (> pos start) collect (subseq string start pos)
        ;  optionally keep delimiter
        when keep-delimiters collect (string (aref string pos))))




(defun isKeyword (string)
    (cdr(assoc string keywordMap :test #'equalp))
)
(defun isOp (string)
    (cdr(assoc string opMap :test #'equalp))
)

;[a-zA-Z_][a-zA-Z0-9_]*
(defun isIdentifier (string)
(setf c(aref string 0))

    (if (not (or  (char= c #\_) (alpha-char-p c ) ))
        (return-from isIdentifier nil)
    )
    
    (loop for c across string 
        do(if (not(or  (char= c #\_) (alpha-char-p c ) ))
                (return-from isidentifier nil))             
    )
    (return-from isIdentifier "IDENTIFIER")
)
        
    
;VALUEI  [0-9]|[1-9][[:digit:]]*
(defun isValueI (string)
    (setf c(aref string 0))
    (if(eql nil (digit-char-p c))
        (return-from isvaluei nil)
    
    )
    (if (= 1(length string))
        (if (not (eql nil (digit-char-p c)))
                
           (return-from isvaluei "VALUEI")
        )
    )
    (if (digit-char-p c)
        (setf c (digit-char-p c))
        (if (> c 0)
            (setf subStr (subseq 1 (length string)))
            (loop for c across substr 
                do(if(eql nil (digit-char-p c))
                (return-from isvaluei nil))             
             )   
        )
    )

    (return-from isvaluei "VALUEI")
    
)
    
    



;VALUEF [0][f][1-9] | [1-9]*[f][1-9]*
(defun isValueF (string)

(setf c(aref string 0))
    
    (setf fFlag 0)
    (if(eql nil (digit-char-p c))
        (return-from isvaluei nil)
    )


)
(defun isString (string)


)
;MENT [;].*
(defun isComment (string)


)


(defun isPharantesis (c) (or (char= c (code-char 40)) (char= c (code-char 41) )))

;split : delimete -> space  (help of stackoverflow)
(defun splitSpace (string  &key (isSpace #'isspace))

  (loop :for start = (position-if-not isSpace string)
    :then (position-if-not isSpace string :start (1+ end))
    :for end = (and start (position-if isSpace string :start start))
    :when start :collect  (subseq string start end) :while end)
)




(defun interpereter (line)

(let ()
                                 
                   (if (and (> (length line) 2) (string-equal(subseq line 0 2) ";;") )
                        (format t "comment~%")
                        (let()(setf lst (splitSpace line))
                        (dolist (str lst)
                        (setf tokenList (splittoken str))
                            (dolist (tokenStr tokenList)
                                ;(write tokenStr)
                                (if (isop tokenstr)
                                    
                                    (format t "~s : ~s~%" tokenStr (isop tokenstr))
                                    ;(write(isop tokenstr))
                                )
                                (if (isvaluei tokenstr)
                                    (format t "~s : ~s~%" tokenStr (isvaluei tokenstr))
                                )
                                (if (iskeyword tokenstr)
                                    (format t "~s : ~s~%" tokenStr (iskeyword tokenstr))
                                    (if (isidentifier tokenstr)
                                    (format t "~s : ~s~%" tokenStr (isidentifier tokenstr))
                                )
                                )
                            
                            )

                        ))
                        
                    )
                        
                )

)
(defun isspace (c) (char= c #\Space))


;interprter using file
(defun interpreterFile (&optional fileName)
    (setq lst nil)
    (let ((in (open fileName))) 
        (loop for line = (read-line in nil)
            do(if(null line)
                (return-from interpreterFile 1)
                ;(write line)
                (interpereter line)
            )
        )
        
    )
)


;interpreter using console inputs
(defun interpreterConsole ()

    (loop
        (setf line (read-line))
	    (if(string-equal line "(exit)")
		    (return-from interpreterconsole 1)
		    (interpereter line)
        )
    )

)

(defun gppinterpereter (&optional (file_name nil))
    (if(not (eq nil file_name))
        (interpreterFile file_name)
        (interpreterConsole)
    )
) 



(defun main()
        (gppinterpereter (car *args*))
        ;(interpreterFile (car *args*))        
)


(main)