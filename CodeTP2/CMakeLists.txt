cmake_minimum_required(VERSION 3.15)
project(CodeTP2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CodeTP2
    src/Principal.cpp
    src/ContratException.cpp
    src/Algorithmes.cpp
    src/Borne.cpp
    src/Trajet.cpp
    src/ReseauBorne.cpp
    src/GestionnaireReseau.cpp
)

# Copie automatique du dossier data/ à côté de l'exécutable pour faciliter l'exécution depuis build/
add_custom_command(TARGET CodeTP2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:CodeTP2>/data)

# Si nécessaire, ajouter les options de compilation spécifiques
# target_compile_options(CodeTP2 PRIVATE -Wall -Wextra -Wpedantic) 