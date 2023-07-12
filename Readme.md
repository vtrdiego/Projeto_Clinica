(DESAFIO) - Sistema para clínica de consultas.

Sistema desenvolvido em linguagem C para utilizar a manipulação de arquivos txt.

Funcionalidades do sistema:

- Cadastra novos pacientes (nome e telefone).
- Cria lista de pacientes cadastrados e marca consultas (dia, horário e especialidade).
- Exclui pacientes e automaticamente exclui consultas do paciente excluído.
- Exclui consultas agendadas.
- Finaliza o sistema.

Tratamento de erros:

- Ao digitar uma opção que não exista, o sistema informa 'OPÇÃO INVÁLIDA!'.
- Sistema verifica se nome inserido é válido (apenas letras e espaços).
- Sistema verifica se telefone inserido é válido (apenas de 8 a 15 dígitos).
- O sistema não cadastra usuários com telefones iguais.
- Ao inserir dia e hora, é verificado se o dia inserido é anterior ao dia atual. Caso seja no mesmo dia, o sistema verifica se o horário inserido já foi ultrapassado no dia.
- Caso o dia inserido seja 30 ou 31, o sistema verifica se o mês atual vai até 30 ou 31.
- Caso o mês para marcar consulta seja fevereiro, o sistema verifica se o ano é bissexto (se fevereiro vai até 28 ou 29).
- Ao inserir dia e hora, o sistema não aceitará dias maiores que o limite do mês atual (28/29/30/31), ou horários maiores que 23.
- Ao inserir dia e hora, o sistema verifica se esse dia e horário já foi agendado.

Obs: 

- O sistema utiliza a biblioteca time.h para se basear na data e hora atual (Dependendo do computador, pode ocorrer imprecisão nos dados atuais).
- O sistema utiliza a biblioteca locale.h para colocar o programa em português, e não ocorrer erros de acentos quando o sistema rodar no terminal.