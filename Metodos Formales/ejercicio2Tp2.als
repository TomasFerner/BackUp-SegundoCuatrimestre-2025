// ======================================================
// Ejercicio 2 - Modelo con instancias fijas
// ======================================================

// Creamos los átomos manualmente

one sig Addr0, Addr1, Addr2 extends Addr {}
one sig Alias0, Alias1 extends Alias {}
one sig Group0 extends Group {}

abstract sig Target {}

abstract sig Name extends Target {
  addressBook: some Target
}

sig Alias extends Name {}
sig Group extends Name {}
sig Addr extends Target {}

// ======================================================
// Instancia exacta del enunciado
// ======================================================

fact instancia {
  // Forzar los conjuntos (ya está garantizado por las sig "one sig")
  Target = Addr + Alias + Group
  Name   = Alias + Group

  // Forzar addressBook exactamente igual al enunciado
  addressBook = 
     (Alias0 -> Addr0) + (Alias0 -> Addr1) + (Alias0 -> Addr2) +
     (Alias0 -> Alias0) + (Alias0 -> Alias1) + (Alias0 -> Group0) +
     (Alias1 -> Addr0) + (Alias1 -> Addr1) + (Alias1 -> Addr2) +
     (Alias1 -> Alias0) + (Alias1 -> Alias1) + (Alias1 -> Group0) +
     (Group0 -> Addr0) + (Group0 -> Addr1) + (Group0 -> Addr2) +
     (Group0 -> Alias0) + (Group0 -> Alias1) + (Group0 -> Group0)
}

// ======================================================
// Comando de ejecución
// ======================================================

run {} for exactly 3 Addr, exactly 2 Alias, exactly 1 Group
