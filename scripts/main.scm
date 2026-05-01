(define (on-init)
  'nil)

(define old-x #f)
(define old-y #f)

(define (on-tick)
  (if (and old-x old-y)
      (let ((dx (- (player-x) old-x))
            (dy (- (player-y) old-y)))
        (skf-log
          (cond
            ((< dx 0) "left")
            ((> dx 0) "right")
            ((< dy 0) "up")
            ((> dy 0) "down")
            (#t "tick")))))
  (set! old-x (player-x))
  (set! old-y (player-y)))
