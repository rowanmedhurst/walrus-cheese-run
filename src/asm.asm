	.assume ADL=1
	.def _fast_isotile_blit_noclip
	.ref __frameset

_fast_isotile_blit_noclip:
	push	iy
	ld	iy,0
	add	iy,sp
	push	hl
	
	ld	bc,(iy+9)
	ld	e,(iy+12)
	ld	hl,(14876692)
	add	hl,bc
	ld	d,320/2
	mlt	de
	add	hl,de
	add	hl,de
	ld	bc,14
	add	hl,bc
	ld	(iy+-3),hl
	
	ld	iy,(iy+6)
	
	ex	de,hl
	lea	hl,iy+16
	ld	c,4
	ldir
	
	ld	hl,318-4
	add	hl,de
	ex	de,hl
	lea	hl,iy+46
	ld	c,8
	ldir
	
	ld	hl,318-8
	add	hl,de
	ex	de,hl
	lea	hl,iy+76
	ld	c,12
	ldir
	
	ld	hl,318-12
	add	hl,de
	ex	de,hl
	lea	hl,iy+106
	ld	c,16
	ldir
	
	ld	hl,318-16
	add	hl,de
	ex	de,hl
	lea	hl,iy+2
	ld	c,134
	add	hl,bc
	ld	c,20
	ldir
	
	ld	hl,318-20
	add	hl,de
	ex	de,hl
	lea	hl,iy+2
	ld	c,164
	add	hl,bc
	ld	c,24
	ldir
	
	ld	hl,318-24
	add	hl,de
	ex	de,hl
	lea	hl,iy+2
	ld	c,194
	add	hl,bc
	ld	c,28
	ldir
	
	ld	hl,318-28
	add	hl,de
	ex	de,hl
	lea	hl,iy+2
	ld	c,194+30
	add	hl,bc
	ld	iy,hl
	ld	c,32
	ldir

	ld	hl,322-32
	add	hl,de
	ex	de,hl
	lea	hl,iy+34
	ld	c,28
	ldir
	
	ld	hl,322-28
	add	hl,de
	ex	de,hl
	lea	hl,iy+68
	ld	c,24
	ldir
	
	ld	hl,322-24
	add	hl,de
	ex	de,hl
	lea	hl,iy+102
	ld	c,20
	ldir
	
	ld	hl,322-20
	add	hl,de
	ex	de,hl
	ld	hl,iy
	ld	c,102+34
	add	hl,bc
	ld	iy,hl
	ld	c,16
	ldir
	
	ld	hl,322-16
	add	hl,de
	ex	de,hl
	lea	hl,iy+34
	ld	c,12
	ldir
	
	ld	hl,322-12
	add	hl,de
	ex	de,hl
	lea	hl,iy+68
	ld	c,8
	ldir
	
	ld	hl,322-8
	add	hl,de
	ex	de,hl
	lea	hl,iy+102
	ld	c,4
	ldir
	
	pop	hl
	pop	iy
	ret
