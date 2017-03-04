	.assume ADL=1
	.def _fast_isotile_blit_noclip
	.ref __frameset

_fast_isotile_blit_noclip:
	push	ix
	ld	ix,0
	add	ix,sp
	push	hl
	
	sbc	hl,hl
	ld	l,(ix+12)
	push	hl
	pop	bc
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	ld	bc,(14876692)
	add	hl,bc
	ld	bc,(ix+9)
	add	hl,bc
	ld	bc,14
	add	hl,bc
	ld	(ix+-3),hl
	
	ex	de,hl
	ld	iy,(ix+6)
	lea	hl,iy+16
	ld	bc,4
	ldir

	ld	hl,(ix+-3)
	ld	de,318
	add	hl,de
	ld	(ix+-3),hl
	ex	de,hl
	lea	hl,iy+46
	ld	bc,8
	ldir
	
	ld	hl,(ix+-3)
	ld	de,318
	add	hl,de
	ld	(ix+-3),hl
	ex	de,hl
	lea	hl,iy+76
	ld	bc,12
	ldir
	
	ld	hl,(ix+-3)
	ld	de,318
	add	hl,de
	ld	(ix+-3),hl
	ex	de,hl
	lea	hl,iy+106
	ld	bc,16
	ldir
	
	ld	hl,(ix+-3)
	ld	de,318
	add	hl,de
	ld	(ix+-3),hl
	ex	de,hl
	lea	hl,iy+2
	ld	bc,134
	add	hl,bc
	ld	bc,20
	ldir
	
	ld	hl,(ix+-3)
	ld	de,318
	add	hl,de
	ld	(ix+-3),hl
	ex	de,hl
	lea	hl,iy+2
	ld	bc,164
	add	hl,bc
	ld	bc,24
	ldir
	
	ld	hl,(ix+-3)
	ld	de,318
	add	hl,de
	ld	(ix+-3),hl
	ex	de,hl
	lea	hl,iy+2
	ld	bc,194
	add	hl,bc
	ld	bc,28
	ldir
	
	ld	hl,(ix+-3)
	ld	de,318
	add	hl,de
	ld	(ix+-3),hl
	ex	de,hl
	lea	hl,iy+2
	ld	bc,194+30
	add	hl,bc
	ld	(ix+-6),hl
	ld	iy,hl
	ld	bc,32
	ldir

	ld	hl,(ix+-3)
	ld	de,322
	add	hl,de
	ld	(ix+-3),hl
	ex	de,hl
	lea	hl,iy+34
	ld	bc,28
	ldir
	
	ld	hl,(ix+-3)
	ld	de,322
	add	hl,de
	ld	(ix+-3),hl
	ex	de,hl
	lea	hl,iy+68
	ld	bc,24
	ldir
	
	ld	hl,(ix+-3)
	ld	de,322
	add	hl,de
	ld	(ix+-3),hl
	ex	de,hl
	lea	hl,iy+102
	ld	bc,20
	ldir
	
	ld	hl,(ix+-3)
	ld	de,322
	add	hl,de
	ld	(ix+-3),hl
	ex	de,hl
	ld	hl,(ix+-6)
	ld	bc,102+34
	add	hl,bc
	ld	(ix+-6),hl
	ld	iy,hl
	ld	bc,16
	ldir
	
	ld	hl,(ix+-3)
	ld	de,322
	add	hl,de
	ld	(ix+-3),hl
	ex	de,hl
	lea	hl,iy+34
	ld	bc,12
	ldir
	
	ld	hl,(ix+-3)
	ld	de,322
	add	hl,de
	ld	(ix+-3),hl
	ex	de,hl
	lea	hl,iy+68
	ld	bc,8
	ldir
	
	ld	hl,(ix+-3)
	ld	de,322
	add	hl,de
	ex	de,hl
	lea	hl,iy+102
	ld	bc,4
	ldir
	
	ld	sp,ix
	pop	ix
	ret	