# cpp_pubsub

Paquete de ejemplo ROS 2 con nodos publicador y suscriptor en C++.

## Nodos

| Nodo | Executable | Tópico | Tipo de mensaje | Descripción |
|------|------------|--------|-----------------|-------------|
| `minimal_publisher` | `publisher_node` | `topic` | `std_msgs/msg/String` | Publica `"Hello, world! N"` cada 500 ms. |
| `listener` | `subscriber_node` | `topic` | `std_msgs/msg/String` | Escucha e imprime lo que publica `publisher_node`. |
| `primos_publisher` | `primos_publisher_node` | `primos` | `std_msgs/msg/Int32` | Publica números primos secuenciales (2, 3, 5, 7, 11, …) cada 1 segundo. |

## Requisitos

- ROS 2 Jazzy (o superior)
- `rclcpp`, `std_msgs`
- `ament_cmake` (build)

## Construcción

Desde el raíz del workspace ROS 2:

```bash
colcon build --packages-select cpp_pubsub
source install/setup.bash
```

## Ejecución

Publicador de primos:

```bash
ros2 run cpp_pubsub primos_publisher_node
```

En otra terminal, escuchar el tópico:

```bash
ros2 topic echo /primos
```

Salida esperada:

```
data: 2
---
data: 3
---
data: 5
---
data: 7
---
data: 11
---
```

Publicador y suscriptor de Strings (para probarlos juntos):

```bash
ros2 run cpp_pubsub publisher_node   # terminal 1
ros2 run cpp_pubsub subscriber_node  # terminal 2
```

## Estilo y contribución

Este proyecto sigue las convenciones de estilo de ROS 2 para C++ (2 espacios de indentación) y se valida con `ament_lint_auto` (copyright, cpplint, lint_cmake, uncrustify). Consulta `CONTRIBUTING.md` para más detalles.

## Licencia

Apache-2.0. Véase `LICENSE`.
