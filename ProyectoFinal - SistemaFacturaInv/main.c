#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Macros para estructura de los clientes.
#define MAXNOM          11
#define MAXAPELL        11
#define MAXNUMTEL       11

// Macros para estructura de los productos.
#define MAXPRODUCTO     30
#define MAXDESCRIPCION  50

// Macros para estructura de los servicios.
#define MAXSERVICIO     30

// Macros para estructura de los empleados.
#define MAXNOMEMP       11
#define MAXAPELEMP      11

// Macros para manejo de archivos.
#define ARCHLOGIN        "login.txt"
#define ARCHCLIENTES     "clientes.txt"
#define ARCHPRODUCTOS    "productos.txt"
#define ARCHSERVICIOS    "servicios.txt"
#define ARCHEMPLEADOS    "empleados.txt"

// Macros para cantidades de inventario.
#define CANTPRODUCTOS     9
#define CANTSERVICIOS     9
#define CANTEMPLEADOS     4
#define CANTCLIENTES      9

// Macros para factura.
#define MAXPRODCOMPRADO   5
#define MAXSERVCOMPRADO   5
#define PORCIENTOPROD     0.0176
#define PORCIENTOSERV     0.05

// Macros para login.
#define MAXUSUARIO        12
#define MAXPASSWORD       12
#define LOGINUNICO        1
#define VALLOGINUNICO     0

// Estructura para login del programa.
typedef struct
{
   char usuario[MAXUSUARIO];
   char password[MAXPASSWORD];

}LOGIN;

// Estructura de los clientes.
typedef struct
{
   char nombre[MAXNOM];
   char apellido[MAXAPELL];
   char num_tel[MAXNUMTEL];

}CLIENTE;

// Estructura de los productos.
typedef struct
{
   char producto[MAXPRODUCTO];
   char descripcion[MAXDESCRIPCION];
   int precio;

}PRODUCTOS;

// Estructura de los servicios.
typedef struct
{
   char servicio[MAXSERVICIO];
   int precio;

}SERVICIOS;

// Estructura de los empleados.
typedef struct
{
   char nom_empleado[MAXNOMEMP];
   char apel_empleado[MAXAPELEMP];

}EMPLEADOS;

// Estructura de la factura.
typedef struct
{
   CLIENTE cliente;
   PRODUCTOS productos[MAXPRODCOMPRADO];
   SERVICIOS servicios[MAXSERVCOMPRADO];
   EMPLEADOS empleado;
   int subtotal_factura;
   float descuento;
   float total_factura;
   float bono_prod_empleado;
   float bono_serv_empleado;
   float bono_total_empleado;

}FACTURA;

// Funciones de registro.
int opciones_registros(void);

// Funciones de control de estructuras.
PRODUCTOS registrar_productos(void);
SERVICIOS registrar_servicios(void);
CLIENTE registrar_clientes(void);
EMPLEADOS registrar_empleados(void);
EMPLEADOS *opc_reg_empleados(void);
PRODUCTOS *opc_reg_productos(void);
SERVICIOS *opc_reg_servicios(void);
CLIENTE *opc_reg_clientes(void);

// Funciones de control de archivos.
void guardar_productos_arch(void);
void guardar_servicios_arch(void);
void guardar_empleados_arch(void);
void guardar_clientes_arch(void);
void cargar_login_arch(LOGIN login[LOGINUNICO]);
void cargar_clientes_arch(CLIENTE clientes[CANTCLIENTES]);
void cargar_productos_arch(PRODUCTOS productos[CANTPRODUCTOS]);
void cargar_servicios_arch(SERVICIOS servicios[CANTSERVICIOS]);
void cargar_empleados_arch(EMPLEADOS empleados[CANTEMPLEADOS]);

// Funciones para facturación.
void facturar(PRODUCTOS productos[CANTPRODUCTOS], SERVICIOS servicios[CANTSERVICIOS], CLIENTE clientes[CANTCLIENTES], EMPLEADOS empleados[CANTEMPLEADOS]);
int buscar_cliente(CLIENTE clientes[CANTCLIENTES], char *n_cliente, char *a_cliente);
int buscar_producto(PRODUCTOS productos[CANTPRODUCTOS], char *nom_producto);
int buscar_servicio(SERVICIOS servicios[CANTSERVICIOS], char *nom_servicio);
int buscar_empleado(EMPLEADOS empleados[CANTEMPLEADOS], char *n_empleado, char *a_empleado);
void imp_factura(FACTURA factura, int cont_producto, int cont_servicio);
void imp_clientes(CLIENTE clientes);
void imp_productos(PRODUCTOS productos);
void imp_servicios(SERVICIOS servicios);
void imp_empleados(EMPLEADOS empleados);

int main()
{
   CLIENTE clientes[CANTCLIENTES];
   PRODUCTOS productos[CANTPRODUCTOS];
   SERVICIOS servicios[CANTSERVICIOS];
   EMPLEADOS empleados[CANTEMPLEADOS];
   LOGIN login[LOGINUNICO];

   int opcion, menu_de_registros, ind_pass;
   char caract;
   char usuario[MAXUSUARIO], password[MAXPASSWORD];

   cargar_login_arch(login);

   do
   {
      ind_pass = 0;
      system("cls");
      printf("Sistema de facturaci%cn e inventario %c [ LINA BEAUTY PLACE ] %c\n\n",162,175,174);
      printf("%c%c Iniciar sesi%cn %c%c\n\n",179,179,162,179,179);
      printf("- [Usuario]     > ");
      fflush(stdin);
      gets(usuario);
      printf("\n- [Contrase%ca]  > ",164);
      while((caract = getch()))
      {
         if(caract == 13)
         {
            password[ind_pass] = '\0';
            break;
         }
         else if(caract == 8)
         {
            if(ind_pass > 0)
            {
               ind_pass--;
               printf("\b \b");
            }
         }
         else
         {
            if(ind_pass < MAXPASSWORD)
            {
               printf("*");
               password[ind_pass] = caract;
               ind_pass++;
            }
         }
      }

      if(strcmp(usuario,login[VALLOGINUNICO].usuario) != 0)
      {
         printf("\n\n[%c] %cError! Usuario incorrecto.\n\n",158,173);
         system("pause");
      }
      else
      {
         if(strcmp(password,login[VALLOGINUNICO].password) != 0)
         {
            printf("\n\n[%c] %cError! Contrase%ca incorrecta.\n\n",158,173,164);
            system("pause");
         }
      }

   }while((strcmp(usuario,login[VALLOGINUNICO].usuario) != 0) || (strcmp(password,login[VALLOGINUNICO].password) != 0));

   do
   {
      system("cls");
      printf("Sistema de facturaci%cn e inventario %c [ LINA BEAUTY PLACE ] %c\n\n",162,175,174);
      printf("%c%c Men%c principal %c%c\n\n",179,179,163,179,179);
      printf("[1] - Registros.\n");
      printf("[2] - Facturaci%cn.\n",162);
      printf("[3] - Salir.\n");
      printf("\nIngrese una opci%cn > ",162);
      scanf("%d",&opcion);

      switch(opcion)
      {
         case 1:
               system("cls");
               menu_de_registros = opciones_registros();
               break;
         case 2:
               system("cls");
               cargar_productos_arch(productos);
               cargar_servicios_arch(servicios);
               cargar_clientes_arch(clientes);
               cargar_empleados_arch(empleados);
               facturar(productos,servicios,clientes,empleados);
               printf("\n");
               system("pause");
               break;
      }

   }while(opcion != 3);

   printf("\n%cGracias por utilizar este software!\n\n",173);
   printf("Desarrollado por [Devs] Carlos Suriel & Esdras Rodr%cguez. %c\n\n",161,169);

   system("pause");
   return 0;
}

void cargar_login_arch(LOGIN login[LOGINUNICO])
{
   FILE *arch_login;

   arch_login = fopen(ARCHLOGIN,"r");

   if(!feof(arch_login))
   {
      fscanf(arch_login,"%s %s\n",login[VALLOGINUNICO].usuario,login[VALLOGINUNICO].password);
   }

   fclose(arch_login);

   return;
}

void facturar(PRODUCTOS productos[CANTPRODUCTOS], SERVICIOS servicios[CANTSERVICIOS], CLIENTE clientes[CANTCLIENTES], EMPLEADOS empleados[CANTEMPLEADOS])
{
   char nom_producto[MAXPRODUCTO], nom_servicio[MAXSERVICIO], n_cliente[MAXNOM], a_cliente[MAXAPELL], n_empleado[MAXNOMEMP], a_empleado[MAXAPELEMP];
   int ind_cliente, ind_producto, cont_producto = 0, ind_servicio, cont_servicio = 0, ind_empleado;
   int agregar_prod, agregar_servicio, resp_prod, resp_servicio, resp_descuento, ver_bono;
   int suma_servicios = 0, suma_productos = 0;
   float porciento_descuento;
   int i;
   FACTURA factura;

   printf("Sistema de facturaci%cn e inventario %c [ LINA BEAUTY PLACE ] %c\n\n",162,175,174);
   printf("%c%c Creaci%cn de factura %c%c\n\n",179,179,162,179,179);
   printf("Nombre [Cliente]   > ");
   fflush(stdin);
   gets(n_cliente);
   printf("\nApellido [Cliente] > ");
   fflush(stdin);
   gets(a_cliente);

   ind_cliente = buscar_cliente(clientes,n_cliente,a_cliente);

   if(ind_cliente == -1)
   {
      printf("\n[%c] %cError! El cliente no est%c registrado.\n",158,173,160);
      return;
   }
   else
   {
      factura.cliente = clientes[ind_cliente];

      do
      {
         printf("\n%cDesea a%cadir productos? [1]-S%c, [0]-No > ",168,164,161);
         scanf("%d",&resp_prod);
      }while(resp_prod  != 1 && resp_prod  != 0);

      if(resp_prod == 1)
      {
         do
         {
            printf("\nNombre [Producto]  > ");
            fflush(stdin);
            gets(nom_producto);

            ind_producto = buscar_producto(productos,nom_producto);

            if(ind_producto == -1)
            {
               printf("\n[%c] %cError! El producto no se encuentra en la base de datos del inventario.\n",158,173);
            }
            else
            {
               if(cont_producto < MAXPRODCOMPRADO)
               {
                  factura.productos[cont_producto] = productos[ind_producto];
                  cont_producto++;
                  do
                  {
                     printf("\n%cDesea a%cadir otro producto? [1]-S%c, [0]-No > ",168,164,161);
                     scanf("%d",&agregar_prod);
                  }while(agregar_prod != 1 && agregar_prod != 0);
               }
               if(cont_producto == MAXPRODCOMPRADO)
               {
                  printf("\n%cAviso! Ha facturado el l%cmite de productos por cliente.\n",173,161);
               }
            }
         }while(cont_producto < MAXPRODCOMPRADO && agregar_prod == 1);
      }

      do
      {
         printf("\n%cDesea a%cadir servicios? [1]-S%c, [0]-No > ",168,164,161);
         scanf("%d",&resp_servicio);
      }while(resp_servicio  != 1 && resp_servicio  != 0);

      if(resp_servicio == 1)
      {
         do
         {
            printf("\nNombre [Servicio]  > ");
            fflush(stdin);
            gets(nom_servicio);

            ind_servicio = buscar_servicio(servicios,nom_servicio);

            if(ind_servicio == -1)
            {
               printf("\n[%c] %cError! El servicio no ha sido identificado.\n",158,173);
            }
            else
            {
               if(cont_servicio < MAXSERVCOMPRADO)
               {
                  factura.servicios[cont_servicio] = servicios[ind_servicio];
                  cont_servicio++;
                  do
                  {
                     printf("\n%cDesea a%cadir otro servicio? [1]-S%c, [0]-No > ",168,164,161);
                     scanf("%d",&agregar_servicio);
                  }while(agregar_servicio != 1 && agregar_servicio != 0);
               }
               if(cont_servicio == MAXSERVCOMPRADO)
               {
                  printf("\n%cAviso! Ha facturado el l%cmite de servicios por cliente.\n",173,161);
               }
            }
         }while(cont_servicio < MAXSERVCOMPRADO && agregar_servicio == 1);
      }

      do
      {
         printf("\nDespachado por > ");
         fflush(stdin);
         scanf("%s %s",n_empleado,a_empleado);

         ind_empleado = buscar_empleado(empleados,n_empleado,a_empleado);

         if(ind_empleado == -1)
         {
            printf("\n[%c] %cError! El empleado no ha sido identificado, introduzca nuevamente nombre y apellido.\n",158,173);
         }
      }while(ind_empleado == -1);

      factura.empleado = empleados[ind_empleado];
   }

   for(i = 0; i < cont_producto; i++)
   {
      suma_productos += factura.productos[i].precio;
   }
   for(i = 0; i < cont_servicio; i++)
   {
      suma_servicios += factura.servicios[i].precio;
   }

   factura.subtotal_factura = suma_productos + suma_servicios;

   factura.bono_prod_empleado = suma_productos*PORCIENTOPROD;

   factura.bono_serv_empleado = suma_servicios*PORCIENTOSERV;

   factura.bono_total_empleado = factura.bono_prod_empleado+factura.bono_serv_empleado;

   do
   {
      printf("\n%cRealizar descuento? [1]-S%c, [0]-No > ",168,161);
      scanf("%d",&resp_descuento);
   }while(resp_descuento  != 1 && resp_descuento  != 0);

   if(resp_descuento == 1)
   {
      printf("\nIngrese el porcentaje de descuento a aplicar > ");
      scanf("%f",&porciento_descuento);

      factura.descuento = factura.subtotal_factura*(porciento_descuento/100);
   }
   else
   {
      factura.descuento = 0;
   }

   factura.total_factura = factura.subtotal_factura-factura.descuento;

   system("cls");

   imp_factura(factura,cont_producto,cont_servicio);

   do
   {
      printf("%cDesea visualizar la bonificaci%cn del empleado? [1]-S%c, [0]-No > ",168,162,161);
      scanf("%d",&ver_bono);
   }while(ver_bono  != 1 && ver_bono  != 0);

   if(ver_bono == 1)
   {
      system("cls");
      printf("Sistema de facturaci%cn e inventario %c [ LINA BEAUTY PLACE ] %c\n\n",162,175,174);
      printf("%c%c Bonificaci%cn del empleado %c%c\n\n",179,179,162,179,179);
      printf("%c Empleado:\n\n",254);
      imp_empleados(factura.empleado);
      printf("\n");
      printf("%c Bonificaci%cn:\n\n",254,162);
      printf("Bonificaci%cn por productos vendidos > RD%c%.2f\n",162,36,factura.bono_prod_empleado);
      printf("Bonificaci%cn por servicios vendidos > RD%c%.2f\n",162,36,factura.bono_serv_empleado);
      printf("Bonificaci%cn total                  > RD%c%.2f\n",162,36,factura.bono_total_empleado);
   }

   return;
}

void imp_factura(FACTURA factura, int cont_producto, int cont_servicio)
{
   int ind;
   printf("Sistema de facturaci%cn e inventario %c [ LINA BEAUTY PLACE ] %c\n\n",162,175,174);
   printf("%c%c Factura realizada %c%c\n\n",179,179,179,179);
   printf("%c Cliente:\n\n",254);
   imp_clientes(factura.cliente);
   printf("\n");
   printf("%c Consumo detallado:\n\n",254);
   for(ind = 0; ind < cont_producto; ind++)
   {
      imp_productos(factura.productos[ind]);
   }
   printf("\n");
   for(ind = 0; ind < cont_servicio; ind++)
   {
      imp_servicios(factura.servicios[ind]);
   }
   printf("\n");
   printf("[Subtotal]  > RD%c%d\n",36,factura.subtotal_factura);
   printf("[Descuento] > RD%c%.2f\n",36,factura.descuento);
   printf("[Total]     > RD%c%.2f\n",36,factura.total_factura);
   printf("\n");
   printf("%c Le atendi%c:\n\n",254,162);
   imp_empleados(factura.empleado);
   printf("\n");

   return;
}

int buscar_cliente(CLIENTE clientes[CANTCLIENTES], char *n_cliente, char *a_cliente)
{
   int ind;

   for(ind = 0; ind < CANTCLIENTES; ind++)
   {
      if(strcmpi(clientes[ind].nombre,n_cliente) == 0)
      {
         if(strcmpi(clientes[ind].apellido,a_cliente) == 0)
         {
            return ind;
         }
      }
   }

   return -1;
}

int buscar_producto(PRODUCTOS productos[CANTPRODUCTOS], char *nom_producto)
{
   int ind;

   for(ind = 0; ind < CANTPRODUCTOS; ind++)
   {
      if(strcmpi(productos[ind].producto,nom_producto) == 0)
      {
         return ind;
      }
   }

   return -1;
}

int buscar_servicio(SERVICIOS servicios[CANTSERVICIOS], char *nom_servicio)
{
   int ind;

   for(ind = 0; ind < CANTSERVICIOS; ind++)
   {
      if(strcmpi(servicios[ind].servicio,nom_servicio) == 0)
      {
         return ind;
      }
   }

   return -1;
}

int buscar_empleado(EMPLEADOS empleados[CANTEMPLEADOS], char *n_empleado, char *a_empleado)
{
   int ind;

   for(ind = 0; ind < CANTEMPLEADOS; ind++)
   {
      if(strcmpi(empleados[ind].nom_empleado,n_empleado) == 0)
      {
         if(strcmpi(empleados[ind].apel_empleado,a_empleado) == 0)
         {
            return ind;
         }
      }
   }

   return -1;
}

void imp_clientes(CLIENTE clientes)
{
   printf("Nombre [Cliente]   > %s\n",clientes.nombre);
   printf("Apellido [Cliente] > %s\n",clientes.apellido);
   printf("N%cmero [Cliente]   > %s\n",163,clientes.num_tel);

   return;
}

void imp_productos(PRODUCTOS productos)
{
   printf("Nombre [Producto]      > %s\n",productos.producto);
   printf("Descripci%cn [Producto] > %s\n",162,productos.descripcion);
   printf("Precio [Producto]      > RD%c%d\n",36,productos.precio);

   return;
}

void imp_servicios(SERVICIOS servicios)
{
   printf("Nombre [Servicio] > %s\n",servicios.servicio);
   printf("Precio [Servicio] > RD%c%d\n",36,servicios.precio);

   return;
}

void imp_empleados(EMPLEADOS empleados)
{
   printf("Nombre [Empleado]   > %s\n",empleados.nom_empleado);
   printf("Apellido [Empleado] > %s\n",empleados.apel_empleado);

   return;
}

int opciones_registros(void)
{
   int opcion;

   do
   {
      system("cls");
      printf("Sistema de facturaci%cn e inventario %c [ LINA BEAUTY PLACE ] %c\n\n",162,175,174);
      printf("%c%c Men%c de registros %c%c\n\n",179,179,163,179,179);
      printf("[1] - Registrar producto.\n");
      printf("[2] - Registrar servicio.\n");
      printf("[3] - Registrar empleado.\n");
      printf("[4] - Registrar cliente.\n");
      printf("[5] - Abandonar.\n");
      printf("\nIngrese una opci%cn > ",162);
      scanf("%d",&opcion);

      switch(opcion)
      {
         case 1:
               system("cls");
               printf("Sistema de facturaci%cn e inventario %c [ LINA BEAUTY PLACE ] %c\n\n",162,175,174);
               printf("%c%c Registro de productos %c%c\n\n",179,179,179,179);
               guardar_productos_arch();
               break;
         case 2:
               system("cls");
               printf("Sistema de facturaci%cn e inventario %c [ LINA BEAUTY PLACE ] %c\n\n",162,175,174);
               printf("%c%c Registro de servicios %c%c\n\n",179,179,179,179);
               guardar_servicios_arch();
               break;
         case 3:
               system("cls");
               printf("Sistema de facturaci%cn e inventario %c [ LINA BEAUTY PLACE ] %c\n\n",162,175,174);
               printf("%c%c Registro de empleados %c%c\n\n",179,179,179,179);
               guardar_empleados_arch();
               break;
         case 4:
               system("cls");
               printf("Sistema de facturaci%cn e inventario %c [ LINA BEAUTY PLACE ] %c\n\n",162,175,174);
               printf("%c%c Registro de clientes %c%c\n\n",179,179,179,179);
               guardar_clientes_arch();
               break;
      }

   }while(opcion != 5);

   return -1;
}

void guardar_productos_arch(void)
{
   FILE *arch_productos;
   PRODUCTOS *productos;
   int ind;

   arch_productos = fopen(ARCHPRODUCTOS,"a");

   productos = opc_reg_productos();

   for(ind = 0; ind < CANTPRODUCTOS; ind++)
   {
      fprintf(arch_productos,"%s %s %d\n",productos[ind].producto, productos[ind].descripcion, productos[ind].precio);
   }

   fclose(arch_productos);

   return;
}

void guardar_servicios_arch(void)
{
   FILE *arch_servicios;
   SERVICIOS *servicios;
   int ind;

   arch_servicios = fopen(ARCHSERVICIOS,"a");

   servicios = opc_reg_servicios();

   for(ind = 0; ind < CANTSERVICIOS; ind++)
   {
      fprintf(arch_servicios,"%s %d\n",servicios[ind].servicio, servicios[ind].precio);
   }

   fclose(arch_servicios);

   return;
}

void guardar_empleados_arch(void)
{
   FILE *arch_empleados;
   EMPLEADOS *empleados;
   int ind;

   arch_empleados = fopen(ARCHEMPLEADOS,"a");

   empleados = opc_reg_empleados();

   for(ind = 0; ind < CANTEMPLEADOS; ind++)
   {
      fprintf(arch_empleados,"%s %s\n",empleados[ind].nom_empleado, empleados[ind].apel_empleado);
   }

   fclose(arch_empleados);

   return;
}

void guardar_clientes_arch(void)
{
   FILE *arch_clientes;
   CLIENTE *clientes;
   int ind;

   arch_clientes = fopen(ARCHCLIENTES,"a");

   clientes = opc_reg_clientes();

   for(ind = 0; ind < CANTCLIENTES; ind++)
   {
      fprintf(arch_clientes,"%s %s %s\n",clientes[ind].nombre, clientes[ind].apellido, clientes[ind].num_tel);
   }

   fclose(arch_clientes);

   return;
}

PRODUCTOS *opc_reg_productos(void)
{
   PRODUCTOS *productos;
   int ind;

   productos = (PRODUCTOS *)malloc(CANTPRODUCTOS*sizeof(PRODUCTOS));

   for(ind = 0; ind < CANTPRODUCTOS; ind++)
   {
      productos[ind] = registrar_productos();
   }

   return productos;
}

SERVICIOS *opc_reg_servicios(void)
{
   SERVICIOS *servicios;
   int ind;

   servicios = (SERVICIOS *)malloc(CANTSERVICIOS*sizeof(SERVICIOS));

   for(ind = 0; ind < CANTSERVICIOS; ind++)
   {
      servicios[ind] = registrar_servicios();
   }

   return servicios;
}

CLIENTE *opc_reg_clientes(void)
{
   CLIENTE *clientes;
   int ind;

   clientes = (CLIENTE *)malloc(CANTCLIENTES*sizeof(CLIENTE));

   for(ind = 0; ind < CANTCLIENTES; ind++)
   {
      clientes[ind] = registrar_clientes();
   }

   return clientes;
}

EMPLEADOS *opc_reg_empleados(void)
{
   EMPLEADOS *empleados;
   int ind;

   empleados = (EMPLEADOS *)malloc(CANTEMPLEADOS*sizeof(EMPLEADOS));

   for(ind = 0; ind < CANTEMPLEADOS; ind++)
   {
      empleados[ind] = registrar_empleados();
   }

   return empleados;
}

PRODUCTOS registrar_productos(void)
{
   PRODUCTOS producto_reg;

   printf("Ingrese el nombre del producto: ");
   fflush(stdin);
   gets(producto_reg.producto);

   printf("Ingrese la descripci%cn del producto: ",162);
   fflush(stdin);
   gets(producto_reg.descripcion);

   printf("Ingrese el precio del producto: ");
   scanf("%d",&producto_reg.precio);

   printf("\n");

   return producto_reg;

}

SERVICIOS registrar_servicios(void)
{
   SERVICIOS servicio_reg;

   printf("Ingrese el nombre del servicio: ");
   fflush(stdin);
   gets(servicio_reg.servicio);

   printf("Ingrese el precio del servicio: ");
   scanf("%d",&servicio_reg.precio);

   printf("\n");

   return servicio_reg;
}

CLIENTE registrar_clientes(void)
{
   CLIENTE cliente_reg;

   printf("Ingrese el nombre del cliente: ");
   fflush(stdin);
   gets(cliente_reg.nombre);

   printf("Ingrese el apellido del cliente: ");
   fflush(stdin);
   gets(cliente_reg.apellido);

   printf("Ingrese el n%cmero de tel%cfono: ",163,130);
   fflush(stdin);
   gets(cliente_reg.num_tel);

   printf("\n");

   return cliente_reg;
}

EMPLEADOS registrar_empleados(void)
{
   EMPLEADOS empleado_reg;

   printf("Ingrese el nombre del empleado: ");
   fflush(stdin);
   gets(empleado_reg.nom_empleado);

   printf("Ingrese el apellido del empleado: ");
   fflush(stdin);
   gets(empleado_reg.apel_empleado);

   printf("\n");

   return empleado_reg;
}

void cargar_clientes_arch(CLIENTE clientes[CANTCLIENTES])
{
   int ind = 0;
   FILE *arch_clientes;

   arch_clientes = fopen(ARCHCLIENTES,"r");

   while(!feof(arch_clientes))
   {
      fscanf(arch_clientes,"%s %s %s\n",clientes[ind].nombre,clientes[ind].apellido,clientes[ind].num_tel);
      ind++;
   }

   fclose(arch_clientes);

   return;
}

void cargar_productos_arch(PRODUCTOS productos[CANTPRODUCTOS])
{
   int ind = 0;
   FILE *arch_productos;

   arch_productos = fopen(ARCHPRODUCTOS,"r");

   while(!feof(arch_productos))
   {
      fscanf(arch_productos,"%s %s %d\n",productos[ind].producto,productos[ind].descripcion,&productos[ind].precio);
      ind++;
   }

   fclose(arch_productos);

   return;
}

void cargar_servicios_arch(SERVICIOS servicios[CANTSERVICIOS])
{
   int ind = 0;
   FILE *arch_servicios;

   arch_servicios = fopen(ARCHSERVICIOS,"r");

   while(!feof(arch_servicios))
   {
      fscanf(arch_servicios,"%s %d\n",servicios[ind].servicio,&servicios[ind].precio);
      ind++;
   }

   fclose(arch_servicios);

   return;
}

void cargar_empleados_arch(EMPLEADOS empleados[CANTEMPLEADOS])
{
   int ind = 0;
   FILE *arch_empleados;

   arch_empleados = fopen(ARCHEMPLEADOS,"r");

   while(!feof(arch_empleados))
   {
      fscanf(arch_empleados,"%s %s\n",empleados[ind].nom_empleado,empleados[ind].apel_empleado);
      ind++;
   }

   fclose(arch_empleados);

   return;
}
