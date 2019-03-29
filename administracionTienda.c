#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <io.h>
#include <string.h>
#include <ctype.h>

//------------------------ESTRUCTURAS--------------------------------------------
struct fecha{
       int dia;
       int mes;
       int anio;
       };
       
struct info{
       char nombreprov[30];
       char nombreempresa[30];
       char rfc[14];
       char direccion[100];
       char telefono[10];
       };
       
struct datos{
       int codigo;
       char nombreprod[30];
       struct fecha entrada;
       struct fecha caducidad;
       float costo;
       struct info proveedor;
       }producto;
       
struct dat{
       char nomarticulo[20];
       float precioart;
       int cantidad;
       }comprobante;
       
struct infoc{
       char nombrec[30];
       char rfcc[14];
       char direccionc[100];
       }consumidor;
       
//--------------------------MENUS--------------------------------------------
int menuuser(void);
int menuroot(void);

//-------------------------INICIALIZANDO FUNCIONES------------------------------
int leer(void);
int mostrarart(void);
int comprar(void);
int hacercompra(void);
int leerticket(void);
int generarticket(void);
int copiar(void);
int verproveedores(void);
int verconsumidores(void);

int alta(void);
int consultarventas(void);
char saltolinea[]="\n";
float total;
char caracter;
FILE *arch1; //registros
FILE *arch5; //obtención de datos
FILE *arch4; //ticket
FILE *arch6; //comprobante para sistema
FILE *arch7; //registro ventas
FILE *arch8; //Datos consumidores
//--------------------------MENU DE USUARIO-------------------------------------
       
int menuuser(void)
{
    int opc2;
    char salidausr;
     system("COLOR 5f");
     do
     {
     system("cls");
     printf("\nQue desea hacer?\n");
     printf("\n\n1.Mostrar productos disponibles.\n\n");
     printf("2.Agregar al carrito.\n\n");
     printf("3.Ver articulos comprados.\n\n");
     printf("4.Generar Ticket (Factura Si lo requiere)(SOLO CUANDO HAYA CONCLUIDO VENTA).\n\n");
     printf("5.Salir.\n\n");
     fflush(stdin);
     scanf("%d", &opc2);
     switch(opc2)
     {
     case 1: mostrarart();break;
     case 2: hacercompra(); break;
     case 3: leerticket(); break;
     case 4: generarticket(); exit(1);
     case 5: break;
     default: printf("\nOpcion no valida\n");
     }
     printf("Desea continuar (realizar otra accion)? (s/n)\n");
    fflush(stdin);
    scanf("%c", &salidausr);
    }while(toupper(salidausr)=='S');
    printf("\n");
    system("pause");
    exit(1);
}
//------------------------------MENU ROOT---------------------------------------    
int menuroot(void)
{
    int opc1;
    char salidaroot;
    system("COLOR fc");
     do
     {
     system("cls");
     printf("\nQue desea hacer?\n");
     printf("\n\n1.Dar de alta producto.\n\n");
     printf("2.Mostrar inventario.\n\n");
     printf("3.Mostrar proveedores.\n\n");
     printf("4.Mostrar consumidores.\n\n");
     printf("5.Copiar datos para uso en ventanilla.\n\n");
     printf("6.Consulta de ventas.\n\n");
     printf("7.Salir.\n\n");
     fflush(stdin);
     scanf("%d", &opc1);
     switch(opc1)
     {
     case 1: alta(); break;
     case 2: leer(); break;
     case 3: verproveedores();break;
     case 4: verconsumidores();break;
     case 5: copiar(); break;
     case 6: consultarventas(); break;
     case 7: break;
     default: printf("\nOpcion no valida\n");
     }
     printf("Desea continuar (realizar otra accion)? (s/n)\n");
    fflush(stdin);
    scanf("%c", &salidaroot);
    }while(toupper(salidaroot)=='S');
    printf("\n");
    system("pause");
    exit(1);
}

//---------------------------------FUNCIONES-------------------------------------

//-------------------FUNCION DAR DE ALTA ARTICULO-------------------------------
int alta(void)
{

arch1 = fopen("registro.dat","a+b"); 
 
char cont1;//continuar ingresando productos

system("cls");
do
{

printf("\nCodigo\n");
fflush(stdin);
scanf("%d", &producto.codigo);
printf("\nNombre\n");
fflush(stdin);
gets(producto.nombreprod);
printf("\nFecha de entrada\n");  
printf("\nDia\n");
fflush(stdin);
scanf("%d", &producto.entrada.dia);
printf("\nMes\n");
fflush(stdin);
scanf("%d", &producto.entrada.mes);
printf("\nAnio\n");
fflush(stdin);
scanf("%d", &producto.entrada.anio);
printf("\nFecha de caducidad\n");  
printf("\nDia\n");
fflush(stdin);
scanf("%d", &producto.caducidad.dia);
printf("\nMes\n");
fflush(stdin);
scanf("%d", &producto.caducidad.mes);
printf("\nAnio\n");
fflush(stdin);
scanf("%d", &producto.caducidad.anio);
printf("\nCosto\n");
fflush(stdin);
scanf("%f", &producto.costo);
printf("\nNombre del proveedor\n");
fflush(stdin);
gets(producto.proveedor.nombreprov);
printf("\nNombre de la empresa\n");
fflush(stdin);
gets(producto.proveedor.nombreempresa);
printf("\nRFC\n");
fflush(stdin);
gets(producto.proveedor.rfc);
printf("\nDireccion\n");
fflush(stdin);
gets(producto.proveedor.direccion);
printf("\nTelefono\n");
fflush(stdin);
gets(producto.proveedor.telefono);

fwrite(&producto,sizeof(producto),1,arch1);

printf("\nDesea ingresar otro articulo? (s/n)\n");
fflush(stdin);
 scanf("%c", &cont1);

}while(toupper(cont1)=='S');

fclose(arch1);

}

//--------------------FUNCION MOSTRAR ARTICULOS ROOT----------------------------
int leer(void)
{
arch1 = fopen("registro.dat","a+b"); 

while(fread(&producto,sizeof(producto),1,arch1)==1)
{
printf("Codigo= %d ",producto.codigo); 
printf("Articulo= %s ",producto.nombreprod);
printf("Entrada= %d/%d/%d ", producto.entrada.dia,producto.entrada.mes,producto.entrada.anio);
printf("Caducidad= %d/%d/%d ", producto.caducidad.dia,producto.caducidad.mes,producto.caducidad.anio);
printf("Costo= %.2f ",producto.costo); 
printf("\n"); 
}; //aqui termina while
fclose(arch1);
}

//-------------------------FUNCION MOSTRAR PROVEEDORES-------------------------
int verproveedores(void)
{
arch1 = fopen("registro.dat","a+b"); 

while(fread(&producto,sizeof(producto),1,arch1)==1)
{
printf("Nombre= %s ",producto.proveedor.nombreprov); 
printf("Empresa= %s ",producto.proveedor.nombreempresa);
printf("RFC= %s ", producto.proveedor.rfc);
printf("Direccion= %s ", producto.proveedor.direccion);
printf("Telefono= %s ",producto.proveedor.telefono); 
printf("\n"); 
}; //aqui termina while
fclose(arch1);
} 

//-------------------------FUNCION MOSTRAR CONSUMIDORES-------------------------
int verconsumidores(void)
{
arch8 = fopen("consumidores.dat","a+b"); 

while(fread(&consumidor,sizeof(consumidor),1,arch8)==1)
{
printf("Nombre= %s ",consumidor.nombrec); 
printf("RFC= %s ", consumidor.rfcc);
printf("Direccion= %s ", consumidor.direccionc);
printf("\n"); 
}; //aqui termina while
fclose(arch8);
} 
  
//-------------------------FUNCION COPIAR DATOS--------------------------------
int copiar(void)
{
arch1 = fopen("registro.dat","a+b"); 
arch5 = fopen("ventas.dat","w+"); 

while(fread(&producto,sizeof(producto),1,arch1)==1)
{
fprintf(arch5, "%s,", producto.nombreprod);
fprintf(arch5, "%.2f ", producto.costo);
};//termina while
fclose(arch1);
fclose(arch5);
}
//-------------------FUNCION VER VENTAS--------------------------
int consultarventas(void)
{
system("cls");
char caracter1;
arch7 = fopen("regventas.dat", "r");//archivo registro de ventas
if(arch7==NULL)
{
    printf ("Sin registro de ventas\n"); system("pause"); exit(1);
}
while(!feof(arch7)) 
    {                              
    caracter1=fgetc(arch7); 
     printf("%c", caracter1);
    }
    
fclose(arch7);
}

//---------------------------FUNCION MOSTRAR ARTICULOS USUARIO-----------------
int mostrarart(void)
{
system("cls");

arch1 = fopen("registro.dat","a+b");

while(fread(&producto,sizeof(producto),1,arch1)==1)
{
printf("* %s ",producto.nombreprod); printf("Codigo= %d", producto.codigo);
printf("\n\n");
};

fclose(arch1);

}

//----------------FUNCION AGREGAR ARTICULO------------------------------------
int hacercompra(void)
{
    //variables para obtencion de precio
    char s3[1000];
	char space[]= " ";
	char coma[]= ",";
	char punto[]= ".";
	char numeros[] = "1234567890";
	char prec[30];
	char precnum[8];
	char precnumaux[8];
	char precionum1[8];
	char ent[4];
	char dec[3];
	float entero;
	int i;
	int j;
//terminan variables obtencion de precio
char cont2;
char nomart[15];
char mystring[1000];
int cantidadaux;
float subtotal=0;

arch5 = fopen("ventas.dat","a+b");
arch6 = fopen("compusr.dat","a+b");//comprobante sistema

do
{ 
printf("\n\nIntroduzca el articulo que desea adquirir?\n");
fflush(stdin);
scanf("%s", nomart);


  fgets (mystring , 1000 , arch5);
  if (strstr(mystring,nomart)!=0)
  {
  strcpy(s3,strstr(mystring,nomart));
	i = strcspn (s3,space);

	for(int n=0;n<i+1;n++)
	{
	prec[n]=s3[n];
	}
	int u=strlen(prec);
	j = strcspn (prec,coma);
	int num = strcspn (prec,numeros);
	strcpy(precnumaux,strstr(prec,coma));
	for (int y=0;y<u-1;y++)
	{
	precnum[y]=precnumaux[y+1];
	}
	int w=strlen(precnum);
	entero=atof(precnum);
	printf("\nCuantas unidades quiere?\n");
    fflush(stdin);
    scanf("%d", &cantidadaux);
    subtotal=(cantidadaux*entero);
    total=total+subtotal;
	strcpy(comprobante.nomarticulo,nomart);
	comprobante.precioart=entero;
	comprobante.cantidad=cantidadaux;
	fwrite(&comprobante,sizeof(comprobante),1,arch6);
	
    }
    else printf("\nArticulo no encontrado\n");
printf("\nDesea comprar otro articulo? (s/n)\n");
fflush(stdin);
scanf("%c", &cont2);

}while(toupper(cont2)=='S');
  
fclose(arch5);
fclose(arch6);

}
//-----------------------FUNCION VER ARTICULOS COMPRADOS----------------------------
int leerticket(void)
{
arch6 = fopen("compusr.dat","a+b");//comprobante sistema

while(fread(&comprobante,sizeof(comprobante),1,arch6)==1)
{ 
printf("Articulo= %s ",comprobante.nomarticulo); 
printf("Precio= %.2f ",comprobante.precioart); 
printf("Cantidad= %d ",comprobante.cantidad); 
printf("\n"); 
}; //aqui termina while
fclose(arch6);
}
//---------------------FUNCION GENERAR TICKET--------------------------------------------
int generarticket(void)
{

char decf;//Opción de factura
arch7 = fopen("regventas.dat", "a+");//archivo registro de ventas
srand (time(NULL));
//------------DATOS TICKET-----------------------------------
char nomtienda[]="QUINTANA";
char direccion[]="ALEMIA No. 10 COL. INDEPENDENCIA DEL. BENITO JUAREZ";
char rfc[]="TAQ-547930-KYT";
char lugar[]="MEXICO DF";
char avisoiva[]="IVA AL 16%";
char sat[]="DOCUMENTO SIN EFECTOS FISCALES";
int ticket;
//-------------------------------------------------------------
char nomticket[8];
float iva;
float tciva;
arch6 = fopen("compusr.dat","a+b");
arch8 = fopen("consumidores.dat","a+b");
printf("\nElija un nombre para identificar su ticket(Entre 5 y 8 letras)\n");
fflush(stdin);
gets(nomticket);
printf("\nRequiere factura?\n");
fflush(stdin);
scanf("%c", &decf);

if(toupper(decf)=='S')
{
//-----------------------REQUIERE FACTURA--------------------------------------
printf("\nPor favor introduzca los datos del cliente\n");
printf("Nombre\n");
fflush(stdin);
gets(consumidor.nombrec);
printf("\nRFC\n");
fflush(stdin);
gets(consumidor.rfcc);
printf("\nDireccion\n");
fflush(stdin);
gets(consumidor.direccionc);


arch4 = fopen(strcat(nomticket,".txt"),"a+");

fprintf(arch4, "       TIENDA %s", nomtienda);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "%s", direccion);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "RFC: %s", rfc);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "%s", lugar);
fprintf(arch4, "%s", saltolinea);

fwrite(&consumidor,sizeof(consumidor),1,arch8);//Guardando datos en archivo (consumidores)

//--------------LUGAR Y FECHA--------------------------------
time_t tiempo = time(0);
		  struct tm *tlocal = localtime(&tiempo);
		  char output[128];
		  strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
		  fprintf(arch4, "HORA Y FECHA DE EXPEDICION: %s\n", output);
//-------------------------------------------------------------
fprintf(arch4, "%s", saltolinea);
srand (time(NULL));
ticket=rand() % 100;
fprintf(arch4, "FOLIO: %d", ticket);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "A  nombre de: %s", consumidor.nombrec);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "RFC: %s", consumidor.rfcc);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "Direccion: %s", consumidor.direccionc);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "%s", saltolinea);

while(fread(&comprobante,sizeof(comprobante),1,arch6)==1)
{
fprintf(arch4, "Articulo: %s ", comprobante.nomarticulo);
fprintf(arch4, "Precio: %.2f ", comprobante.precioart);
fprintf(arch4, "Cantidad: %d", comprobante.cantidad);
fprintf(arch4, "%s", saltolinea);
};
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "SUBTOTAL: %.2f", total);
fprintf(arch4, "%s", saltolinea);
iva=total*0.16;
tciva=total+total*0.16;
fprintf(arch4, "IVA: %.2f", iva);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "TOTAL: %.2f", tciva);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "NOTA: %s", avisoiva);
fprintf(arch4, "%s", saltolinea);

//--------------COPIANDO TICKET Y TOTAL A REGISTRO----------------------------
fprintf(arch7, "TICKET: %d ", ticket);
fprintf(arch7, "TOTAL: %.2f", tciva);
fprintf(arch7, "%s", saltolinea);
//----------------------------------------------------------------------------
}
else
{
arch4 = fopen(strcat(nomticket,".txt"),"a+");

fprintf(arch4, "       TIENDA %s", nomtienda);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "%s", direccion);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "RFC: %s", rfc);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "%s", lugar);
fprintf(arch4, "%s", saltolinea);


//--------------LUGAR Y FECHA--------------------------------
time_t tiempo = time(0);
		  struct tm *tlocal = localtime(&tiempo);
		  char output[128];
		  strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
		  fprintf(arch4, "HORA Y FECHA DE EXPEDICION: %s\n", output);
//-------------------------------------------------------------
fprintf(arch4, "%s", saltolinea);
srand (time(NULL));
ticket=rand() % 100;
fprintf(arch4, "TICKET: %d", ticket);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "%s", saltolinea);

while(fread(&comprobante,sizeof(comprobante),1,arch6)==1)
{
fprintf(arch4, "Articulo: %s ", comprobante.nomarticulo);
fprintf(arch4, "Precio: %.2f ", comprobante.precioart);
fprintf(arch4, "Cantidad: %d", comprobante.cantidad);
fprintf(arch4, "%s", saltolinea);
};
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "SUBTOTAL: %.2f", total);
fprintf(arch4, "%s", saltolinea);
iva=total*0.16;
tciva=total+total*0.16;
fprintf(arch4, "IVA: %.2f", iva);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "TOTAL: %.2f", tciva);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "NOTA: %s", avisoiva);
fprintf(arch4, "%s", saltolinea);
fprintf(arch4, "%s", sat);
//--------------COPIANDO TICKET Y TOTAL A REGISTRO----------------------------
fprintf(arch7, "TICKET: %d ", ticket);
fprintf(arch7, "TOTAL: %.2f", tciva);
fprintf(arch7, "%s", saltolinea);
//----------------------------------------------------------------------------
}   
total=0;
fclose(arch4);
fclose(arch6);
fclose(arch7);
fclose(arch8);

remove("compusr.dat");

}


//------------------------MAIN-------------------------------------------------
int main(void)
{
  int opcg;
  int salida;
  system("COLOR 2c");
  do{
  system("cls");
  printf("\nBienvenido al sistema\n");
  printf("Elija la opcion que necesite\n");
  printf("\n1.Administracion\n");
  printf("2.Vender\n");
  fflush(stdin);
     scanf("%d", &opcg);
  switch(opcg)
     {
     case 1: menuroot();/*alta();*/ break;
     case 2: menuuser();/*modificar();*/ break;
     default: printf("\nOpcion no valida\n");
     }
     printf("Desea regresar al menu? (s/n)\n");
    fflush(stdin);
    scanf("%c", &salida);
    }while(toupper(salida)!='S');
    printf("\n\n");
    system("pause");
}
    
    
