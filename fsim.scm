#!/usr/bin/env guile
!#
; https://www.unix-ag.uni-kl.de/~guenther/guile-scripts-howto.html
(use-modules (gl) (glut))
(initialize-glut (program-arguments) #:window-size '(320 . 200) #:display-mode (display-mode rgb double depth))
(define main-window (make-window "fgsim"))
(set-display-callback (lambda ()
  (gl-clear (clear-buffer-mask color-buffer depth-buffer))
  (swap-buffers)))
(glut-main-loop)
