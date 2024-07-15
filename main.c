#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char nome[20];
    bool eTercerizado;
    float salario;
    float valor_hora;
    int horas_trabalhadas;
    int contratos_assinados;
    float comissao_por_contrato;
} Funcionario;

Funcionario funcionarios[] = {};
int numero_de_funcionarios = 0;


/* 
    Função para cadastrar um funcionário
    @param nome: nome do funcionário
    @param eTercerizado: se o funcionário é tercerizado
    @param salario: salário do funcionário
    @param valor_hora: valor da hora trabalhada
    @param horas_trabalhadas: horas trabalhadas
    @param contratos_assinados: quantidade de contratos assinados
    @param comissao_por_contrato: comissão por contrato
    @return int: retorna o número identificador do funcionário cadastrado
*/
int cadastrarFuncionario(
    char *nome,
    bool eTercerizado,
    float salario,
    float valor_hora,
    int horas_trabalhadas,
    int contratos_assinados,
    float comissao_por_contrato
) {
    if (strlen(nome) == 0) {
        printf("Nome do funcionário não pode ser vazio\n");
        return -1;
    }

    Funcionario funcionario;
    strcpy(funcionario.nome, nome);
    funcionario.eTercerizado = eTercerizado;

    if(eTercerizado) {
    funcionario.valor_hora = valor_hora;
    funcionario.horas_trabalhadas = horas_trabalhadas;
    } else {
    funcionario.salario = salario;
    }

    if(contratos_assinados > 0) {
        funcionario.contratos_assinados = contratos_assinados;
        funcionario.comissao_por_contrato = comissao_por_contrato;
    } else {
        funcionario.contratos_assinados = 0;
    }

    funcionarios[numero_de_funcionarios] = funcionario;
    numero_de_funcionarios++;
    printf("Funcionário %s cadastrado com o ID %i\n", funcionario.nome, numero_de_funcionarios);

    return numero_de_funcionarios;
}

/*
    Função para calcular o pagamento de um funcionário
    @param id: identificador do funcionário
    @return float: retorna o valor do pagamento do funcionário
*/
float calcularPagamentoAUmFuncionario(int id) {
    Funcionario funcionario = funcionarios[id - 1];
    int total = 0;
    if(funcionario.eTercerizado) {
        total = funcionario.valor_hora * funcionario.horas_trabalhadas;
    } else {
        total = funcionario.salario;
    }

    if (funcionario.contratos_assinados) {
        total += funcionario.contratos_assinados * funcionario.comissao_por_contrato;
    }

    return total;
}

/*
    Função para calcular a folha de pagamento
    @return float: retorna o valor total da folha de pagamento
*/
float calcularFolhaDePagamento() {
    float total = 0;
    for(int i = 0; i < numero_de_funcionarios; i++) {
        total += calcularPagamentoAUmFuncionario(i + 1);
    }
    return total;
}

int main(void) {
    cadastrarFuncionario("Lucas Rayan", false, 2000, 0, 0, 5, 100);
    cadastrarFuncionario("Lucas Guerra", true, 0, 50, 40, 0, 100);

    printf("%.2f\n", calcularPagamentoAUmFuncionario(1));
    printf("%.2f\n", calcularPagamentoAUmFuncionario(2));

    printf("Folha de pagamento: %.2f\n", calcularFolhaDePagamento());

    return 0;
}
