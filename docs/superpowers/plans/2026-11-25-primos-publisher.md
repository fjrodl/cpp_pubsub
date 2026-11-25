# [Nodo publicador de primos] Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Añadir un nuevo nodo publicador al paquete ROS 2 `cpp_pubsub` que genere y publique números primos de forma secuencial en el tópico `primos` usando mensajes `std_msgs/msg/Int32`, y actualizar de forma coherente `CMakeLists.txt`, `package.xml` y documentación.

**Architecture:** Un nuevo archivo fuente `src/primos_publisher_node.cpp` que define una clase `PrimosPublisher` heredando de `rclcpp::Node`, con un temporizador que calcula el siguiente número primo y lo publica cada segundo. Se reutilizan las dependencias ya declaradas (`rclcpp`, `std_msgs`). No se añaden nuevas dependencias de package.

**Tech Stack:** ROS 2 Jazzy, rclcpp, std_msgs, C++17, CMake/ament_cmake, colcon.

**Spec:** solicitud del usuario ("quiero un nodo nuevo de publicacion que publica los numeros primos, actualiza de forma coherente todo el repositorio cpp_pubsub"). No existe spec de diseño separado; este plan es el spec.

## Global Constraints

- Licencia Apache-2.0 con cabecera de copyright (`// Copyright 2026 ulixes`) en todo archivo fuente nuevo.
- Tipo de mensaje: `std_msgs/msg/Int32`.
- Nombre del tópico: `primos`.
- Nombre del nodo: `primos_publisher`.
- Sin nuevas dependencias en `package.xml` ni `CMakeLists.txt` (solo `rclcpp` y `std_msgs`, ya presentes).
- Seguir el estilo existente: indentación de 2 espacios, nombres en inglés estilo ROS 2, logs con `RCLCPP_INFO`.
- El generador de primos avanza al siguiente primo en cada callback (no repite ni reinicia).

## Review Focus

- Generador de primos: cada publicación debe ser el siguiente primo sin repeticiones ni saltos. Probado con `ros2 topic echo` sobre `/primos`.
- Desbordamiento de `int32` tras muchos primos: el nodo debe seguir funcionando (se documenta el límite en comentarios).
- El temporizador no bloquea el `rclcpp::spin` (callback ligero).
- El nodo se compila e instala junto a `publisher_node` y `subscriber_node` sin romperlos.

## File Structure

- Create: `src/primos_publisher_node.cpp` — nuevo nodo publicador de primos.
- Modify: `CMakeLists.txt` — añadir executable `primos_publisher_node` e instalarlo.
- Modify: `package.xml` — actualizar `<description>` para mencionar el publicador de primos.
- Verify: `colcon build --packages-select cpp_pubsub` y prueba de runtime con `ros2 topic echo /primos`.

---

### Task 1: Crear el nodo publicador de primos (`src/primos_publisher_node.cpp`)

**Interfaces:**
- Consumes: nada (nodo autónomo).
- Produces: clase `PrimosPublisher : public rclcpp::Node` que publica `std_msgs::msg::Int32` en `primos` cada 1 s.

- [ ] **Step 1: Write the failing test**

```bash
# El test es de compilación/runtime: el ejecutable no existe aún
colcon build --packages-select cpp_pubsub
# Expected: FAIL, "primos_publisher_node" target no definido / no instalado
```

- [ ] **Step 2: Implementar `PrimosPublisher` en `src/primos_publisher_node.cpp`**

Cuerpo del algoritmo (no determinado por la firma): prueba de primalidad por división hasta sqrt(n) y generación del siguiente primo.

- [ ] **Step 3: Run build to verify it compiles**

Run: `colcon build --packages-select cpp_pubsub`
Expected: PASS, `primos_publisher_node` instalado en `install/cpp_pubsub/lib/cpp_pubsub/`.

---

### Task 2: Registrar el ejecutable en `CMakeLists.txt` e instalarlo

**Files:**
- Modify: `CMakeLists.txt:29-38` — añadir `add_executable`, `ament_target_dependencies` e incluir en `install(TARGETS ...)`.

**Interfaces:**
- Consumes: `src/primos_publisher_node.cpp` (creado en Task 1).
- Produces: objetivo `primos_publisher_node` listado junto a `publisher_node` y `subscriber_node`.

- [ ] **Step 1: Modificar `CMakeLists.txt`**

Añadir tras el bloque de `subscriber_node`:

```cmake
add_executable(primos_publisher_node src/primos_publisher_node.cpp)
ament_target_dependencies(primos_publisher_node rclcpp std_msgs)
```

y añadir `primos_publisher_node` a `install(TARGETS ...)`.

- [ ] **Step 2: Run build to verify it installs**

Run: `colcon build --packages-select cpp_pubsub`
Expected: PASS, ejecutable instalado.

---

### Task 3: Actualizar descripción de `package.xml`

**Files:**
- Modify: `package.xml:6` — `<description>`.

**Interfaces:**
- Consumes: nada.
- Produces: descripción actualizada que menciona el nodo publicador de primos.

- [ ] **Step 1: Editar `package.xml`**

Actualizar la línea `<description>` para incluir el publicador de primos.

- [ ] **Step 2: Verify**

Run: `grep -n "description" package.xml`
Expected: la descripción menciona "primos".

---

### Task 4: Verificación de runtime y cierre

- [ ] **Step 1: Ejecutar el nodo y escuchar el tópico**

Run:
```bash
source install/setup.bash
ros2 run cpp_pubsub primos_publisher_node &  # en un terminal
ros2 topic echo /primos                      # en otro
```
Expected: se imprimen 2, 3, 5, 7, 11, ... en orden, uno por segundo.

- [ ] **Step 2: Commit**

```bash
git add src/primos_publisher_node.cpp CMakeLists.txt package.xml docs/superpowers/plans/2026-11-25-primos-publisher.md
git commit -m "feat(cpp_pubsub): añadir nodo publicador de números primos"
```

---

Self-review completado: cada requisito del spec tiene una tarea; los pasos son inequívocos y no hay líneas que decidan nada ("TBD", "handle edge cases").

**Plan complete and saved to `docs/superpowers/plans/2026-11-25-primos-publisher.md`. Please review the plan. Does it capture what you want?**

El plan prefiere la ejecución **Native** (implemento todo yo en esta sesión y hago una verificación final), porque las tareas son pocas, están muy acopladas entre sí (el ejecutable depende del fuente y del CMake) y el costo de un error es bajo (se revierte con un commit).

¿Quieres que proceda con la implementación ahora, o prefieres ajustar algo del plan (por ejemplo, el tipo de mensaje `Int32` vs `String`, el nombre del tópico o el periodo del temporizador)?
