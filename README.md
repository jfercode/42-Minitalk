# 42-Minitalk 📡
**`Minitalk`** implementa un sistema de comunicación entre un cliente y un servidor utilizando señales de 'UNIX' (SIGUSR1 y SIGUSR2). El cliente envía mensajes al servidor bit a bit, codificando los caracteres en señales, mientras que el servidor decodifica estos mensajes y los muestra en la salida estándar.

## ¿Cómo se manejan las señales? 🧠

La comunicación en Minitalk se basa en señales de UNIX para enviar datos entre procesos.

### 📡 Señales de UNIX (SIGUSR1 y SIGUSR2)
- **`SIGUSR1`** = bit 0
- **`SIGUSR2`** = bit 1

Se utilizan para transmitir información binaria bit a bit.

### ⚙️ Manejo de Señales
**`signal()`** Simple, pero limitado.

**`sigaction()`** Más robusto y seguro, recomendado para gestionar múltiples señales de forma eficiente.

### 🔄 Comunicación Asíncrona
Las señales pueden llegar en cualquier momento, por lo que el servidor debe estar siempre listo para recibirlas sin bloquear su ejecución.

### ✉️ Codificación de Caracteres
El cliente convierte cada carácter en 8 bits y los envía usando señales. El servidor reconstruye los bits en caracteres y muestra el mensaje.

### ⏱️ Sincronización y Errores
Se usa `usleep()` para evitar pérdidas de señales. Opcionalmente, se puede implementar un ACK para confirmar la recepción de datos.

### ⚠️ Condiciones de Carrera
Se mitigan usando `sigaction()` con configuraciones adecuadas para manejar señales rápidamente sin errores.

## Cómo ejecutar 🖥️

Los siguientes comandos deben ser ejecutados en la terminal, dentro del directorio de tu proyecto:

- **`make all`**: Compila el proyecto y genera los ejecutables `client`y `server`
- **`make clean`**: Elimina los archivos objeto (`.o`) generados durante la compilación.
- **`make fclean`**: Ejecuta el comando `clean` y, además, elimina el ejecutable `pipex`.
- **`make re`**: Ejecuta los comandos `fclean` y `all`, recompilando todo el proyecto desde cero.

## Uso del programa 🏃

Una vez generado los archivos, para probar la comunicación etre cliente y servidor primero deberás de ejecutar el servidor, este te mostrará el `PID` del mismo lo que permitirá posteriormente su comunicación. 

```sh
./server    
SERVER_PID: 354495
```

Posteriormente en otra terminal, ejecutaremos el cliente seguido del PID que devuelve el servidor y de un mensaje que se le va a mandar.

```sh
./client 354495 "Hello Server"
```
Si todo ha ido bien se mostrará el mensaje en la terminal del servidor  y en la del cliente un mensaje de confirmación predeterminado.

```sh 
./server    
SERVER_PID: 354495
Hello Server
```
```sh
./client 354495 "Hello Server"
        ✅ Message received ✅
```

### Casos de error ⚠️
En este proyecto, la ejecución del cliente fallará en caso de que no se le pasen los comandos correctamente al cliente, así como el PID del servidor no corresponda a un proceso de ejecución.

```sh
./client <server_pid> "message_to_send"
```

## Configuración ⚙️

Puedes ajustar las opciones de compilación en el Makefile según tus necesidades específicas. 

## Autor 👨‍💻
  <br/>
  <br/>
  <br/>

</div>
<div align="center">
  <img src="https://avatars.githubusercontent.com/u/102600920?v=4" alt="Logo" width="200"/>
  <br/>
  <br/>
  <div style="margin: 20px 0 30px;">
  <a href="https://github.com/jfercode">Javier Fernández Correa</a>
  </div>
</div>
  <br/>
<div align="center">
  <img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTVInHuUPtp3uiEuvF0aYAkFBUzpnr65b2CDA&s" alt="Logo"/>
</div>
<br/>
</div>
