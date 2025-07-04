import re

def validar_cpf(cpf: str) -> bool:
    """
    Valida um CPF a partir de uma string de 11 dígitos numéricos.

    Esta função realiza o cálculo dos dígitos verificadores para determinar
    se o CPF é matematicamente válido, seguindo o algoritmo da Receita Federal.

    Args:
        cpf (str): Uma string contendo exatamente 11 dígitos numéricos.

    Returns:
        bool: True se o CPF for válido, False caso contrário.
    """
    # Condição 1: Verifica se todos os dígitos são iguais (ex: "111.111.111-11")
    if cpf == cpf[0] * 11:
        return False

    # --- Cálculo do 1º Dígito Verificador ---
    soma_digito1 = sum(int(cpf[i]) * (10 - i) for i in range(9))
    resto_digito1 = (soma_digito1 * 10) % 11
    if resto_digito1 == 10: # Se o resto for 10, o dígito é 0
        resto_digito1 = 0
    
    if resto_digito1 != int(cpf[9]):
        return False

    # --- Cálculo do 2º Dígito Verificador ---
    soma_digito2 = sum(int(cpf[i]) * (11 - i) for i in range(10))
    resto_digito2 = (soma_digito2 * 10) % 11
    if resto_digito2 == 10: # Se o resto for 10, o dígito é 0
        resto_digito2 = 0
        
    if resto_digito2 != int(cpf[10]):
        return False
        
    # Se passou por todas as verificações, o CPF é válido
    return True

def scan_cpf() -> str:
    """
    Solicita a entrada de um CPF ao usuário, valida e o retorna formatado.
    
    O loop continua até que um CPF válido seja inserido.
    """
    while True:
        cpf_input = input("Digite o CPF: ").strip()
        
        # Remove todos os caracteres não numéricos usando expressão regular
        cpf_numerico = re.sub(r'\D', '', cpf_input)
        
        # Verifica se o CPF possui 11 dígitos após a limpeza
        if len(cpf_numerico) != 11:
            print("Erro: O CPF deve conter 11 dígitos. Tente novamente.")
            continue # Volta para o início do loop

        # Chama a função de validação
        if validar_cpf(cpf_numerico):
            # Formata o CPF para exibição padrão
            cpf_formatado = f"{cpf_numerico[:3]}.{cpf_numerico[3:6]}.{cpf_numerico[6:9]}-{cpf_numerico[9:]}"
            print(f"CPF válido: {cpf_formatado}")
            return cpf_formatado
        else:
            # Informa que é inválido e permite uma nova tentativa
            print("CPF inválido! Tente novamente.")

# Bloco de execução principal
if __name__ == "__main__":
    cpf_validado = scan_cpf()
