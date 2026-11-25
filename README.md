# cpp_pubsub

Paquete de ejemplo para **ROS 2** que implementa un nodo **publicador** y un nodo **suscriptor** en C++.
El publicador envía periódicamente mensajes de tipo `std_msgs/String` al tópico `topic`, y el suscriptor los recibe e imprime por consola.

Este repositorio sirve como punto de partida para aprender la comunicación básica entre nodos en ROS 2 usando C++ y `rclcpp`.

---

## Estructura del repositorio

```
ros2_ws/src/
└── cpp_pubsub/                 # Paquete ROS 2
    ├── CMakeLists.txt          # Configuración de compilación (ament_cmake)
    ├── package.xml             # Manifiesto del paquete (dependencias, licencia, mantenedor)
    ├── LICENSE                 # Licencia Apache 2.0
    ├── src/
    │   ├── publisher_node.cpp  # Nodo publicador
    │   └── subscriber_node.cpp # Nodo suscriptor
    └── README.md               # Este archivo
```

---

## Requisitos previos

- [ROS 2](https://docs.ros.org/en/jazzy/Installation.html) instalado (por ejemplo, Humble, Iron o Jazzy).
- Un *workspace* de ROS 2 configurado (por ejemplo, `~/ros2_ws`).
- Este repositorio clonado dentro de `ros2_ws/src/`.

---

## Instalación y compilación

Desde la raíz de tu workspace de ROS 2:

```bash
# 1. Asegúrate de estar en el workspace
cd ~/ros2_ws

# 2. Instala las dependencias del paquete
rosdep install --from-paths src --ignore-src -r -y

# 3. Compila el paquete
colcon build --packages-select cpp_pubsub

# 4. Configura el entorno
source install/setup.bash
```

---

## Cómo ejecutar

Se necesitan dos terminales: una para el publicador y otra para el suscriptor.

### Terminal 1 — Ejecutar el suscriptor

```bash
source install/setup.bash
ros2 run cpp_pubsub subscriber_node
```

Salida esperada:

```
[INFO] [subscriber_node]: I heard: 'Hello, world! 0'
[INFO] [subscriber_node]: I heard: 'Hello, world! 1'
[INFO] [subscriber_node]: I heard: 'Hello, world! 2'
...
```

### Terminal 2 — Ejecutar el publicador

```bash
source install/setup.bash
ros2 run cpp_pubsub publisher_node
```

Salida esperada:

```
[INFO] [minimal_publisher]: Publishing: 'Hello, world! 0'
[INFO] [minimal_publisher]: Publishing: 'Hello, world! 1'
[INFO] [minimal_publisher]: Publishing: 'Hello, world! 2'
...
```

El publicador envía un mensaje cada **500 ms** al tópico `topic`, con un contador que se incrementa en cada envío (`Hello, world! 0`, `Hello, world! 1`, …).

---

## Verificación con herramientas de ROS 2

Puedes inspeccionar el tópico desde una terminal adicional:

```bash
source install/setup.bash

# Listar tópicos activos
ros2 topic list

# Escuchar el tópico 'topic'
ros2 topic echo /topic

# Obtener información del tópico
ros2 topic info /topic
```

---

## Explicación del código

### `src/publisher_node.cpp`

Define la clase `MinimalPublisher`, heredada de `rclcpp::Node`:

- Crea un publicador sobre el tópico `topic` con mensajes `std_msgs::msg::String` y una cola de 10 mensajes.
- Configura un temporizador (`create_wall_timer`) que se dispara cada 500 ms.
- En cada disparo, construye un mensaje `"Hello, world! <contador>"`, lo imprime en el log y lo publica.

### `src/subscriber_node.cpp`

Define la clase `MinimalSubscriber`, heredada de `rclcpp::Node`:

- Crea una suscripción al tópico `topic` con mensajes `std_msgs::msg::String` y una cola de 10 mensajes.
- Cada vez que llega un mensaje, imprime su contenido en el log con `I heard: '<mensaje>'`.

---

## Tópicos y mensajes

| Elemento   | Valor                  |
|------------|------------------------|
| Tópico     | `topic`                |
| Tipo       | `std_msgs/msg/String`  |
| Publicador | `publisher_node`       |
| Suscriptor | `subscriber_node`      |
| Frecuencia | 2 Hz (cada 500 ms)     |

---

## Licencia

Este proyecto está bajo la **Licencia Apache 2.0**. Consulta el archivo [`LICENSE`](cpp_pubsub/LICENSE) para más detalles.

---

## Mantenedor

- **ulixes** <fjrodl@unileon.es>

---

> Nota: los archivos `package.xml` y `CMakeLists.txt` contienen marcadores `TODO` y configuraciones de linter desactivadas por defecto, tal como se generan desde la plantilla estándar de ROS 2. Puedes completarlos según las necesidades de tu proyecto.