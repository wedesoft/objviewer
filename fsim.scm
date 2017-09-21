#!/usr/bin/env guile
!#
; https://www.unix-ag.uni-kl.de/~guenther/guile-scripts-howto.html
(use-modules (gl) (glu) (glut))

(initialize-glut (program-arguments) #:window-size '(320 . 200) #:display-mode (display-mode rgb double depth))

(define main-window (make-window "fgsim"))

(set-reshape-callback (lambda (width height)
  (gl-viewport 0 0 width height)
  (set-gl-matrix-mode (matrix-mode projection))
  (gl-load-identity)
  (glu-perspective 60 (/ width height) 0.1 1000)))

(set-display-callback (lambda ()
  (gl-clear (clear-buffer-mask color-buffer depth-buffer))
  (swap-buffers)))

(set-keyboard-callback (lambda (keycode x y)
  (case (integer->char keycode)
    ((#\esc #\q) (exit)))))

(glut-main-loop)
