# AGENT.md — Información para agentes de IA

Este archivo describe las características y convenciones del repositorio `ros2_ws/src` para facilitar el trabajo de cualquier agente de IA que lo utilice.

## Resumen del repositorio

Este workspace de ROS 2 contiene el paquete `cpp_pubsub`, un ejemplo de comunicación entre nodos en C++ usando `rclcpp`. Implementa un nodo publicador y un nodo suscriptor que intercambian mensajes `std_msgs/String` en el tópico `topic`.

## Estructura

```
ros2_ws/src/
└── cpp_pubsub/                 # Paquete ROS 2 (ament_cmake)
    ├── CMakeLists.txt          # Build y reglas de linting
    ├── package.xml             # Manifiesto del paquete
    ├── LICENSE                 # Apache License 2.0
    ├── CONTRIBUTING.md         # Guía de contribución + texto de licencia
    ├── README.md               # Documentación del proyecto
    ├── AGENT.md                # Este archivo
    └── src/
        ├── publisher_node.cpp  # Publica "Hello, world! <n>" cada 500 ms en /topic
        ├── subscriber_node.cpp # Recibe mensajes de /topic y los imprime
        └── primos_publisher_node.cpp  # Publica números primos en /primos (Int32)
```

## Lenguajes y herramientas

- **C++14** (ROS 2 estilo: 2 espacios de indentación)
- **Sistema de compilación:** `ament_cmake` / `colcon`
- **Linters activados:** `ament_lint_auto` (copyright, cpplint, lint_cmake, uncrustify)
- **Dependencias:** `rclcpp`, `std_msgs`
- **Licencia:** Apache License 2.0
- **Mantenedor:** ulixes <fjrodl@unileon.es>

## Cómo compilar y probar

Desde la raíz del workspace (`ros2_ws/`):

```bash
source /opt/ros/<distro>/setup.bash   # ej. humble, iron, jazzy
rosdep install --from-paths src --ignore-src -r -y
colcon build --packages-select cpp_pubsub
source install/setup.bash
colcon test --packages-select cpp_pubsub
```

## Cómo ejecutar los nodos

Terminal 1 (suscriptor):
```bash
source install/setup.bash
ros2 run cpp_pubsub subscriber_node
```

Terminal 2 (publicador):
```bash
source install/setup.bash
ros2 run cpp_pubsub publisher_node
```

## Convenciones de código

- Indentación: **2 espacios** (estilo ROS 2 / uncrustify)
- Cada archivo fuente `.cpp` debe tener cabecera de copyright Apache 2.0 al inicio
- Cada archivo debe terminar con salto de línea (newline al final)
- No hay espacios en blanco al final de línea (trailing whitespace)
- `ament_lint_auto` se ejecuta automáticamente con `colcon test`

## Archivos generados (no versionar)

- `build/`, `install/`, `log/` — generados por `colcon`

## Licencia

Todo el contenido está bajo la **Licencia Apache 2.0**, salvo que se indique lo contrario.
