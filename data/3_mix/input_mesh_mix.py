$input.vertex[]=[]
$input.element[]=[]
$input.region[]=[]
nx,ny=10,10
lx,ly=10.0,10.0
dx,dy=lx/nx,ly/ny
my=4
#vertex
index=0
for j in range(ny+1):
	y=j*dy
	for i in range(nx+1):
		x=i*dx
		$input.vertex[index].id=index
		$input.vertex[index].position=[x,y]
		index+=1
#element
index=0
for j in range(my):
	for i in range(nx):
		vi=(nx+1)*j+i
		$input.element[index].id=index
		$input.element[index].vertex[]=[(nx+1)*j+i,(nx+1)*j+i+1,(nx+1)*(j+1)+i+1,(nx+1)*(j+1)+i]
		index+=1
for j in range(my,ny):
	for i in range(nx):
		vi=(nx+1)*j+i
		$input.element[index].id=index
		$input.element[index].vertex[]=[(nx+1)*j+i,(nx+1)*j+i+1,(nx+1)*(j+1)+i]
		index+=1
		$input.element[index].id=index
		$input.element[index].vertex[]=[(nx+1)*(j+1)+i,(nx+1)*j+i+1,(nx+1)*(j+1)+i+1]
		index+=1
#region
$input.region[0].type="phi"
$input.region[0].phi=0.0
$input.region[0].name="down"
for i in range(1,nx):
	$input.region[0].vertex[i-1]=i
$input.region[1].type="phi"
$input.region[1].phi=1.0
$input.region[1].name="up"
for i in range(1,nx):
	$input.region[1].vertex[i-1]=ny*(nx+1)+i
$input.region[2].type="q"
$input.region[2].q=0.0
$input.region[2].name="left"
for j in range(ny+1):
	$input.region[2].vertex[j]=j*(nx+1)
$input.region[3].type="q"
$input.region[3].q=0.0
$input.region[3].name="right"
for j in range(ny+1):
	$input.region[3].vertex[j]=j*(nx+1)+nx
